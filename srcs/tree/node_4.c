/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 03:36:29 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 03:44:01 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_second(t_list *token, t_lexer *lex, t_node_creator *cr)
{
	if (!ft_strcmp("|", token->content))
	{
		if (pipe_node(lex, cr))
			return (1);
	}
	else if (!ft_strcmp(";", token->content))
	{
		if (semi_colon_node(lex, cr))
			return (1);
	}
	else if (cmd_node(lex, token, cr))
		return (1);
	return (0);
}

int		handle_first(t_list *token, t_lexer *lex, t_node_creator *cr)
{
	if (is_redir(">", token->content))
	{
		if (supp_node(lex, token, cr))
			return (1);
	}
	else if (is_redir("<", token->content))
	{
		if (inf_node(lex, token, cr))
			return (1);
	}
	else if (is_redir(">>", token->content))
	{
		if (d_supp_node(lex, token, cr))
			return (1);
	}
	else if (handle_second(token, lex, cr))
		return (1);
	return (0);
}
