/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:58:10 by lgrellie          #+#    #+#             */
/*   Updated: 2021/01/26 20:31:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		from_general(t_lexer *lex)
{
	lex->prev_state = e_general;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]))
		lex->state = e_general;
	else if (lex->input[lex->token_start + lex->token_len] == '>')
		lex->state = e_supp;
	else if (lex->input[lex->token_start + lex->token_len] == '<')
 		lex->state = e_inf;
	else if (lex->input[lex->token_start + lex->token_len] == ';')
		lex->state = e_semi_colon;
	else if (lex->input[lex->token_start + lex->token_len] == '&')
		lex->state = e_and;
	else if (lex->input[lex->token_start + lex->token_len] == '|')
		lex->state = e_or;
	else if (lex->input[lex->token_start + lex->token_len])
		lex->state = e_word;
}

void        from_word(t_lexer *lex)
{
	lex->prev_state = e_word;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]))
		lex->state = e_general;
	else if (lex->input[lex->token_start + lex->token_len] == '>')
		lex->state = e_supp;
	else if (lex->input[lex->token_start + lex->token_len] == '<')
		lex->state = e_inf;
    else if (lex->input[lex->token_start + lex->token_len] == ';')
		lex->state = e_semi_colon;
    else if (lex->input[lex->token_start + lex->token_len] == '&')
		lex->state = e_and;
    else if (lex->input[lex->token_start + lex->token_len] == '|')
		lex->state = e_or;
    else
		lex->state = e_word;
}

void		from_s_quote(t_lexer *lex)
{
	lex->prev_state = e_s_quote;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_word;
}

void		from_d_quote(t_lexer *lex)
{
	lex->prev_state = e_d_quote;
	if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_word;
	if (lex->input[lex->token_start + lex->token_len] == '\\')
	{
		lex->prev_state = lex->state;
		lex->state = e_backslash;
	}
}

void		from_backslash(t_lexer *lex)
{
	if (lex->prev_state == e_d_quote)
		lex->state = lex->prev_state;
	else
		lex->state = e_word;
	lex->prev_state = e_backslash;
}
