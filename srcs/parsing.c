/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:29:41 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 01:12:52 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_num_in_word(char **first, char *index, int num)
{
	char	*numstr;
	char	*concat;

	numstr = ft_itoa(num);
	num = ft_strlen(numstr);
	if (!numstr)
		return (M_ERROR);
	pop_substr(index, 2);
	concat = ft_strnew(ft_strlen(*first) + num);
	if (!concat)
		return (M_ERROR);
	ft_strncpy(concat, *first, index - *first);
	ft_strcat(concat, numstr);
	ft_strcat(concat, index);
	free(numstr);
	free(*first);
	*first = concat;
	return (num);
}

int	insert_word(t_lexer *lex, char *word, char **first, char *check)
{
	char	*key;
	char	*exp;
	char	*concat;

	while (is_name_char(*word))
		word++;
	key = ft_substr(check, 0, word - check);
	if (!key)
		return (M_ERROR);
	exp = get_var_value(lex->env_list, key);
	free(key);
	pop_substr(check - 1, word - check + 1);
	word = check - 1;
	if (exp)
	{
		concat = ft_strnew(ft_strlen(*first) + ft_strlen(exp));
		if (!concat)
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

void	sub_filter_word(char *word, int len)
{
	shift_from_index(word, 0);
	shift_from_index(word, len - 1);
}

int	expand_word(t_lexer *lex, char *word, char **first)
{
	int w_start;
	int len;

	w_start = 0;
	len = 0;
	lex->state = e_word;
	while (*word)
	{
		if (lex->state == e_backslash)
			expand_backslash_state_case(lex, first, &w_start, &len, &word);
		else if (*word == '"' &&
			(lex->state == e_word || lex->state == e_d_quote))
			expand_dquote_case(lex, first, &w_start, &len, &word);
		else if (*word == '\'' &&
			(lex->state == e_word || lex->state == e_s_quote))
			expand_squote_case(lex, first, &w_start, &len, &word);
		else if (*word == '\\' && lex->state != e_s_quote)
			expand_backslash_case(lex);
		else if (*word == '$' && lex->state != e_s_quote)
			expand_dollar_case(lex, first, &w_start, &len, &word);
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
