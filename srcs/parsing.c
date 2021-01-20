/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:29:41 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/20 00:19:25 by cjaimes          ###   ########.fr       */
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

int insert_word(t_lexer *lex, char *word, char **first, char *check)
{
	char *key;
	char *exp;
	char *concat;

	while (is_name_char(*word))
		word++;
	if (!(key = ft_substr(check, 0, word - check)))
		return (FAILURE);
	exp = get_var_value(lex->env_list, key);
	free(key);
	pop_substr(check - 1, word - check + 1);
	word = check - 1;
	if (exp)
	{
		if (!(concat = ft_strnew(ft_strlen(*first) + ft_strlen(exp))))
			return (FAILURE);
		ft_strncpy(concat, *first, check - 1 - *first);
		ft_strcat(concat, exp);
		ft_strcat(concat, word);
		free(*first);
		*first = concat;
		word = *first + ft_strlen(concat) - ft_strlen(word);
	}
	else
		return (0);
	return (ft_strlen(exp));
}

void sub_filter_word(char *word, int len)
{
	int counter;
	char cur;

	cur = 0;
	counter = 0;
	//ft_printf("filtered world: %s\n", word);
	shift_from_index(word, 0);
	//ft_printf("filtered world: %s\n", word);
	shift_from_index(word, len - 1);
	//ft_printf("filtered world: %s\n", word);
	// while (*word && len--)
	// {
	// 	if ((*word == '\'' || *word == '"'))
	// 	{
	// 		if (!cur)
	// 			cur = *word;
	// 		if (front == -1)
	// 			front = counter;
	// 		else if (*word == cur)
	// 		{
	// 			shift_from_index(word - counter, front);
	// 			shift_from_index(word - 1, 0);
	// 			word -= 2;
	// 			counter -= 2;
	// 			front = -1;
	// 			cur = 0;
	// 			continue;
	// 		}
	// 	}
	// 	word++;
	// 	counter++;
	// }
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
			if (lex->prev_state == e_word)
			{
				shift_from_index(word - 1, 0);
				w_start = word - *first;
				word--;
				lex->state = e_word;
			}
			else if (lex->prev_state == e_d_quote && (*word == '\\' || *word == '$' || *word == '"'))
			{
				//ft_printf("before |%s|\n", word - 1);
				//ft_printf("before |%s|\n", *first);
				shift_from_index(word - 1, 0);
				word--;
				//ft_printf("after  |%s|\n", word - 1);
				//ft_printf("after  |%s|\n", *first);
				//w_start = word - *first;
				len++;
				lex->state = e_d_quote;
			}
			else
			{
				lex->state = lex->prev_state;
				len += 2;
			}
			
		}
		else if (*word == '"' && (lex->state == e_word || lex->state == e_d_quote))
		{
			//ft_printf("d quote\n");
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
				// after word expansion, word isn't attached to first anymore
				len += insert_word(lex, word + 2, first, word + 1);
				word = *first + len - 1;
				//word--;
			}
		}
		else
			len++;	
		word++;
	}
	return (SUCCESS);
}

int expand_word1(t_lexer *lex, char *word, char **first)
{
	int w_start;
	int dur;

	w_start = 0;
	dur = 0;
	while (*word)
	{
		//ft_printf("Expanding: %s - state %d  - current word : %s - w_start %d - dur %d\n", *first, lex->state, word, w_start, dur);
		//keeps literal value outside of word
		if (lex->state == e_backslash && lex->prev_state == e_word)
		{
			//ft_printf("removing slash\n");
			shift_from_index(word - 1, 0);
			w_start += dur;
			word--;
			dur = 0;
			lex->state = e_word;
		}
		else if (lex->state == e_backslash && lex->prev_state == e_d_quote && (*word == '\\' || *word == '$' || *word == '"'))
		{
			//ft_printf("here\n");
			if (*word == '\\' || *word == '$' || *word == '"')
			{
				shift_from_index(word - 1, 0);
				word--;
				if (lex->prev_state == e_d_quote)
				{
					lex->state = lex-> prev_state;
					lex->prev_state = e_backslash;
				}
			}
			lex->state = e_d_quote;
			lex->prev_state = e_word;
			//w_start++;
			dur++;
		}
		else if (lex->state == e_backslash && lex->prev_state == e_d_quote)
		{
			lex->state = e_d_quote;
			dur++;
		}
		else if (*word == '\'' && (lex->state == e_word || lex->state == e_s_quote))
		{
			lex->state = lex->state == e_word? e_s_quote : e_word;
			if (lex->state == e_word)
			{
				//ft_printf("removing s quotes\n");
				sub_filter_word(*first + w_start, dur);
				word -= 2;
				w_start += ++dur - 2; 
				dur = 0;
			}
			else 
			{
				////ft_printf("enterring s quotes\n");
				w_start += dur;
				dur = 1;
			}
		}
		else if (*word == '"' && (lex->state == e_word || lex->state == e_d_quote)) {
			lex->state = lex->state == e_word? e_d_quote : e_word;
			if (lex->state == e_word) {
				//ft_printf("removing d quotes\n");

				sub_filter_word(*first + w_start, dur);
				word -= 2;
				w_start += ++dur - 2; 
				dur = 0;
			}
			else
			{
				//ft_printf("enterring d quotes\n");
				w_start += dur;
				dur = 1;
			}
		}
		else if (*word == '\\' && lex->state != e_s_quote)
		{
			if (lex->prev_state != e_d_quote)
			{
				//w_start += dur;
				dur = 1;
			}
			//ft_printf("entering backslash state\n");
			lex->prev_state = lex->state;
			lex->state = e_backslash;
		}
		else if (*word == '$' && lex->state != e_s_quote)
		{
			if ((ft_isalpha(*(word + 1)) || *(word + 1) == '_'))
				insert_word(lex, word + 2, first, word + 1);
		}
		else
			dur++;
		//ft_printf("Expanding: %s - state %d  - current word : %s - w_start %d - dur %d\n", *first, lex->state, word, w_start, dur);
		word++;
	}
	return (SUCCESS);
}

void filter_word(char *word)
{
	int front;
	int counter;
	char cur;

	cur = 0;
	counter = 0;
	front = -1;
	while (*word)
	{
		if ((*word == '\'' || *word == '"'))
		{
			if (!cur)
				cur = *word;
			if (front == -1)
				front = counter;
			else if (*word == cur)
			{
				shift_from_index(word - counter, front);
				shift_from_index(word - 1, 0);
				word -= 2;
				counter -= 2;
				front = -1;
				cur = 0;
				continue;
			}
		}
		word++;
		counter++;
	}
}

int	treat_word(t_lexer *lex, t_node *node)
{
	if (expand_word(lex, node->content, (char **)&(node->content)) == FAILURE)
		return (FAILURE);
	//filter_word(node->content);
	return (SUCCESS);
}
