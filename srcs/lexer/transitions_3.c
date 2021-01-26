/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:31:13 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:31:42 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		from_and(t_lexer *lex)
{
	lex->prev_state = e_and;
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
