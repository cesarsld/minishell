/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:58:10 by lgrellie          #+#    #+#             */
/*   Updated: 2020/02/25 13:34:05 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		from_general(t_lexer *lex)
{
	lex->prev_state = e_general;
	if (c == '\'')
		lex->state = e_s_quote;
	else if (c == '"')
		lex->state = e_d_quote;
	else if (c == '\\')
		lex->state = e_backslash;
	else if (is_white_space(c))
		lex->state = e_general;
	else if (c == '>')
		lex->state = e_supp;
	else if (c == '<')
 		lex->state = e_inf;
	else if (c == ';')
		lex->state = e_semi_colon;
	else if (c == '&')
		lex->state = e_and;
	else if (c == '|')
		lex->state = e_or;
	else
		lex->state = e_word;
}

void        from_word(t_lexer *lex)
{
	lex->prev_state = e_word;
	if (c == '\'')
		lex->state = e_s_quote;
	else if (c == '"')
		lex->state = e_d_quote;
	else if (c == '\\')
		lex->state = e_backslash;
	else if (is_white_space(c))
		lex->state = e_general;
	else if (c == '>')
		lex->state = e_supp;
	else if (c == '<')
		lex->state = e_inf;
    else if (c == ';')
		lex->state = e_semi_colon;
    else if (c == '&')
		lex->state = e_and;
    else if (c == '|')
		lex->state = e_or;
    else
		lex->state = e_word;
}

void		from_s_quote(t_lexer *lex)
{
	lex->prev_state = e_s_quote;
	if (c == '\'')
		lex->state = e_general;
}

void		from_d_quote(t_lexer *lex)
{
	lex->prev_state = e_d_quote;
	if (c == '"')
		lex->state = e_general;

}
void					from_backslash(t_lexer *lex)
{
	//lex->prev_state = e_backslash;
	lex->state = lex->prev_state;
	lex->prev_state = e_backslash;
}

// create and token at some point
void					from_and(t_lexer *lex)
{
	lex->prev_state = e_and;
	if (c == '\'')
		lex->state = e_s_quote;
	else if (c == '"')
		lex->state = e_d_quote;
	else if (c == '\\')
		lex->state = e_backslash;
	else if (is_white_space(c))
		lex->state = e_general;
	else if (c == '>')
		lex->state = e_supp;
	else if (c == '<')
 		lex->state = e_inf;
	else if (c == ';')
		lex->state = e_semi_colon;
	else if (c == '&')
		lex->state = e_and;
	else if (c == '|')
		lex->state = e_or;
	else
		lex->state = e_word;

}
void					from_or(t_lexer *lex)
{
	lex->prev_state = e_and;
	if (c == '\'')
		lex->state = e_s_quote;
	else if (c == '"')
		lex->state = e_d_quote;
	else if (c == '\\')
		lex->state = e_backslash;
	else if (is_white_space(c))
		lex->state = e_general;
	else if (c == '>')
		lex->state = e_supp;
	else if (c == '<')
 		lex->state = e_inf;
	else if (c == ';')
		lex->state = e_semi_colon;
	else if (c == '&')
		lex->state = e_and;
	else if (c == '|')
		lex->state = e_or;
	else
		lex->state = e_word;
}
void					from_semi_colon(t_lexer *lex);
void					from_supp(t_lexer *lex);
void					from_inf(t_lexer *lex);
void					from_error(t_lexer *lex);
