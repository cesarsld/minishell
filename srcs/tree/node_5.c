/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:40:30 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/01 21:40:53 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_name_node(t_lexer *lex, t_list *token, t_node_creator *cr)
{
	char *temp;

	if (!cr->stack && !(cr->stack = create_new_node(e_t_cmd_name)))
		return (1);
	if (cr->stack_head && cr->stack_head->type == e_t_pipe)
		cr->stack_head->right = cr->stack;
	else
		cr->stack_head = cr->stack;
	if (!(temp = ft_strdup((char*)token->content)))
		return (1);
	cr->stack->content = temp;
	cr->cur_cmd = cr->stack;
	if (cr->redir_head)
		cr->cur_cmd->right = cr->redir_head;
	lex->p_token = e_t_cmd_name;
	return (0);
}

int	cmd_name_node_2(t_lexer *lex, t_list *token, t_node_creator *cr)
{
	char *temp;

	if (cr->stack->type == e_t_cmd_name ||
		cr->stack->type == e_t_cmd_word)
	{
		if (!(cr->temp = create_new_node(e_t_cmd_word)))
			return (1);
		if (!(temp = ft_strdup((char*)token->content)))
			return (1);
		cr->temp->content = temp;
		cr->stack->left = cr->temp;
		cr->stack = cr->stack->left;
	}
	lex->p_token = e_t_cmd_word;
	return (0);
}

int	cmd_node(t_lexer *lex, t_list *token, t_node_creator *cr)
{
	char *temp;

	if (lex->p_token == e_t_supp || lex->p_token == e_t_inf ||
		lex->p_token == e_t_d_supp)
	{
		if (!(temp = ft_strdup((char*)token->content)))
			return (1);
		cr->redir->content = temp;
		lex->p_token = e_t_word;
	}
	else if (!cr->stack || !cr->stack->content)
	{
		if (cmd_name_node(lex, token, cr))
			return (1);
	}
	else
	{
		if (cmd_name_node_2(lex, token, cr))
			return (1);
	}
	return (0);
}
