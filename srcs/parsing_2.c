/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:55:06 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:55:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_backslash_state_case(t_lexer *lex, char **first, int *w_start, int *len,
	char **word)
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

void expand_dquote_case(t_lexer *lex, char **first, int *w_start, int *len,
	char **word)
{
	lex->state = lex->state == e_word? e_d_quote : e_word;
	if (lex->state == e_d_quote) {
		*w_start = *word - *first;
		*len = 1;
	}
	else
	{
		sub_filter_word(*first + *w_start, *len);
		(*word) -=2;
		*w_start = *word - *first;
		*len = 0;
	}
}

void expand_squote_case(t_lexer *lex, char **first, int *w_start, int *len,
	char **word)
{
	lex->state = lex->state == e_word? e_s_quote : e_word;
	if (lex->state == e_s_quote)
	{
		*w_start = *word - *first;
		*len = 1;
	}
	else
	{
		sub_filter_word(*first + *w_start, *len);
		*word -=2;
		*w_start = *word - *first;
		*len = 0;
	}
}

void expand_backslash_case(t_lexer *lex)
{
	lex->prev_state = lex->state;
	lex->state = e_backslash;
}

void expand_dollar_case(t_lexer *lex, char **first, int *w_start, int *len,
	char **word)
{
	if ((ft_isalpha(*(*word + 1) ) || *(*word + 1) == '_'))
	{
		*len += insert_word(lex, *word + 2, first, *word + 1);
		*word = *first + *w_start + *len - 1;
	}
	else if (*(*word + 1) == '?')
	{
		*len += insert_num_in_word(first, *word, *lst_rtn());
		*word = *first + *w_start + *len - 1;
	}
	else
		(*len)++;
}
