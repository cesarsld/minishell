/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:24:32 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:06:48 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		push_token(t_lexer *lex)
{
	char	*str;
	t_list	*token;
	
	if (lex->token_len == 0)
		return (0);
	if (!(str = ft_substr(lex->input, lex->token_start, lex->token_len)))
		return (1);
	if (!(token = ft_lstnew(str)))
	{
		free(str);
		return (1);
	}
	ft_lstadd_back(&(lex->tokens), token);
	lex->token_start += ft_strlen(str);
	lex->token_len = 0;
	return (0);
}

int		grow_token(t_lexer *lex)
{
	lex->token_len += 1;
	return (0);
}

int		discard_one(t_lexer *lex)
{
	lex->token_start += 1;
	lex->token_len = 0;
	return (0);
}

int			act_general(t_lexer *lex)
{
	if (lex->token_len)
		return (push_token(lex));
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
			!lex->input[lex->token_start + lex->token_len])
		return (discard_one(lex));
	return (0);
}
