/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:24:34 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:28:57 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			act_or(t_lexer *lex)
{
	if (lex->token_len && lex->prev_state != e_or)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (lex->prev_state == e_or)
	{
		if (push_token(lex))
			return (1);
		lex->state = e_general;
	}
	return (0);
}

int			act_semi_colon(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}

int			act_supp(t_lexer *lex)
{
	if (lex->token_len && lex->prev_state != e_supp &&
		is_number_n(lex->input + lex->token_start, lex->token_len))
	{
		grow_token(lex);
		return (0);
	}
	else if (lex->token_len && lex->prev_state != e_supp)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (lex->prev_state == e_supp)
	{
		if (push_token(lex))
			return (1);
		lex->state = e_general;
	}
	return (0);
}

int			act_inf(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}

int			act_error(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}
