/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:29:41 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:45:12 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_whitespace(char **line)
{
	while (is_white_space(**line))
		(*line)++;
}

char	*ft_strjoin_input(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = malloc((len + 2) * sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len + 2);
	ft_strlcat(new, "\n", len + 2);
	ft_strlcat(new, s2, len + 2);
	return (new);
}

void shift_from_index(char *line, int index)
{
	int i;

	i = 0;
	while (*(line + index + i))
	{
		*(line + index + i) = *(line + index + i + 1);
		i++;
	}
}

void pop_substr(char *start, int amount)
{
	while (*(start + amount))
	{
		*start = *(start + amount);
		start++;
	}
	*start = 0;
}

int is_name_char(char c)
{
	return (ft_isalnum(c) || c ==  '_');
}

int insert_num_in_word(char **first, char *index, int num)
{
	char *numstr;
	char *concat;

	numstr = ft_itoa(num);
	num = ft_strlen(numstr);
	if (!numstr)
		return (M_ERROR);
	pop_substr(index, 2);
	if (!(concat = ft_strnew(ft_strlen(*first) + num)))
		return (M_ERROR);
	ft_strncpy(concat, *first, index - *first);
	ft_strcat(concat, numstr);
	ft_strcat(concat, index);
	free(numstr);
	free(*first);
	*first = concat;
	return (num);
}

int insert_word(t_lexer *lex, char *word, char **first, char *check)
{
	char *key;
	char *exp;
	char *concat;

	while (is_name_char(*word))
		word++;
	if (!(key = ft_substr(check, 0, word - check)))
		return (M_ERROR);
	exp = get_var_value(lex->env_list, key);
	free(key);
	pop_substr(check - 1, word - check + 1);
	word = check - 1;
	if (exp)
	{
		if (!(concat = ft_strnew(ft_strlen(*first) + ft_strlen(exp))))
			return (M_ERROR);
		ft_strncpy(concat, *first, check - 1 - *first);
		ft_strcat(concat, exp);
		ft_strcat(concat, word);
		free(*first);
		*first = concat;
		word = *first + ft_strlen(concat) - ft_strlen(word);
	}
	return (exp ? ft_strlen(exp) : 0);
}

void sub_filter_word(char *word, int len)
{
	shift_from_index(word, 0);
	shift_from_index(word, len - 1);
}

void expand_backslash_case(t_lexer *lex, char **first, int *w_start, int *len, char **word)
{
	if (lex->prev_state == e_word)
	{
		shift_from_index(*word - 1, 0);
		*w_start = *word - *first;
		(*word)--;
		lex->state = e_word;
	}
	else if (lex->prev_state == e_d_quote && (**word == '\\' || **word == '$' || **word == '"'))
	{
		shift_from_index(*word - 1, 0);
		(*word)--;
		(*len)++;
		lex->state = e_d_quote;
	}
	else
	{
		lex->state = lex->prev_state;
		(*len) += 2;
	}
}

int expand_word(t_lexer *lex, char *word, char **first)
{
	int w_start;
	int len;

	w_start = 0;
	len = 0;
	lex->state = e_word;
	while (*word)
	{
		//ft_printf("Expanding: %s - state %d  - current word : |%s| - w_start %d - dur %d\n", *first, lex->state, word, w_start, len);
		if (lex->state == e_backslash)
		{
			expand_backslash_case(lex, first, &w_start, &len, &word);
		}
		else if (*word == '"' && (lex->state == e_word || lex->state == e_d_quote))
		{
			lex->state = lex->state == e_word? e_d_quote : e_word;
			if (lex->state == e_d_quote) {
				w_start = word - *first;
				len = 1;
			}
			else
			{
				sub_filter_word(*first + w_start, len);
				word -=2;
				w_start = word - *first;
				len = 0;
			}
		}
		else if (*word == '\'' && (lex->state == e_word || lex->state == e_s_quote))
		{
			lex->state = lex->state == e_word? e_s_quote : e_word;
			if (lex->state == e_s_quote)
			{
				w_start = word - *first;
				len = 1;
			}
			else
			{
				sub_filter_word(*first + w_start, len);
				word -=2;
				w_start = word - *first;
				len = 0;
			}
		}
		else if (*word == '\\' && lex->state != e_s_quote)
		{
			lex->prev_state = lex->state;
			lex->state = e_backslash;
		}
		else if (*word == '$' && lex->state != e_s_quote)
		{
			if ((ft_isalpha(*(word + 1) ) || *(word + 1) == '_'))
			{
				len += insert_word(lex, word + 2, first, word + 1);
				word = *first + w_start + len - 1;
			}
			else if (*(word + 1) == '?')
			{
				len += insert_num_in_word(first, word, *lst_rtn());
				word = *first + w_start + len - 1;
			}
			else
				len++;
		}
		else
			len++;	
		word++;
	}
	return (SUCCESS);
}

int	treat_word(t_lexer *lex, t_node *node)
{
	if (expand_word(lex, node->content, (char **)&(node->content)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
