/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:31:10 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:31:35 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		from_or(t_lexer *lex)
{
	lex->prev_state = e_or;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
		!lex->input[lex->token_start + lex->token_len])
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

void		from_semi_colon(t_lexer *lex)
{
	lex->prev_state = e_semi_colon;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
		!lex->input[lex->token_start + lex->token_len])
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

void		from_supp(t_lexer *lex)
{
	lex->prev_state = e_supp;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
		!lex->input[lex->token_start + lex->token_len])
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

void		from_inf(t_lexer *lex)
{
	lex->prev_state = e_inf;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
		!lex->input[lex->token_start + lex->token_len])
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

void		from_error(t_lexer *lex)
{
	lex->prev_state = e_error;
	if (lex->input[lex->token_start + lex->token_len] == '\'')
		lex->state = e_s_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '"')
		lex->state = e_d_quote;
	else if (lex->input[lex->token_start + lex->token_len] == '\\')
		lex->state = e_backslash;
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
		!lex->input[lex->token_start + lex->token_len])
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
