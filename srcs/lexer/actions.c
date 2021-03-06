/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:24:41 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:29:32 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			act_word(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf ||
		lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_s_quote(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf ||
		lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_d_quote(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf ||
		lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_backslash(t_lexer *lex)
{
	grow_token(lex);
	return (0);
}

int			act_and(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	discard_one(lex);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}
