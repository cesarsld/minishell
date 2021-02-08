/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:59:50 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/07 13:35:56 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_supp_err(t_lexer *lex)
{
	if (lex->p_token == e_t_d_supp || lex->p_token == e_t_supp ||
		lex->p_token == e_t_inf)
	{
		ft_printf_err("minishell: syntax error near unexpected token `>'\n");
		*lst_rtn() = 2;
		return (1);
	}
	if (lex->p_token == e_t_semi_colon || lex->p_token == e_t_pipe)
	{
		ft_printf_err(
			"minishell: syntax error near unexpected token `newline'\n");
		*lst_rtn() = 2;
		return (1);
	}
	return (0);
}

int	supp_node(t_lexer *lex, t_list *token, t_node_creator *cr)
{
	if (handle_supp_err(lex))
		return (1);
	if (!(cr->temp = create_new_node(e_t_supp)))
		return (1);
	cr->temp->fd = get_number(token->content, ft_strlen(token->content) - 1);
	if (!cr->redir_head)
		cr->redir_head = cr->temp;
	else
		cr->redir->left = cr->temp;
	cr->redir = cr->temp;
	if (cr->cur_cmd)
		cr->cur_cmd->right = cr->redir_head;
	else
	{
		if (!(cr->stack = create_new_node(e_t_cmd_name)))
			return (1);
		cr->stack->right = cr->redir_head;
		cr->cur_cmd = cr->stack;
		if (cr->stack_head && cr->stack_head->type == e_t_pipe)
			cr->stack_head->right = cr->stack;
		else
			cr->stack_head = cr->stack;
	}
	lex->p_token = e_t_supp;
	return (0);
}

int	handle_inf_err(t_lexer *lex)
{
	if (lex->p_token == e_t_d_supp || lex->p_token == e_t_supp ||
		lex->p_token == e_t_inf)
	{
		ft_printf_err("minishell: syntax error near unexpected token `<'\n");
		*lst_rtn() = 2;
		return (1);
	}
	if (lex->p_token == e_t_semi_colon || lex->p_token == e_t_pipe)
	{
		ft_printf_err(
			"minishell: syntax error near unexpected token `newline'\n");
		*lst_rtn() = 2;
		return (1);
	}
	return (0);
}

int	inf_node(t_lexer *lex, t_list *token, t_node_creator *cr)
{
	if (handle_inf_err(lex) || !(cr->temp = create_new_node(e_t_inf)))
		return (1);
	cr->temp->fd = get_number(token->content, ft_strlen(token->content) - 1);
	if (cr->temp->fd == 1)
		cr->temp->fd = 0;
	if (!cr->redir_head)
		cr->redir_head = cr->temp;
	else
		cr->redir->left = cr->temp;
	cr->redir = cr->temp;
	if (cr->cur_cmd)
		cr->cur_cmd->right = cr->redir_head;
	else
	{
		if (!(cr->stack = create_new_node(e_t_cmd_name)))
			return (1);
		cr->stack->right = cr->redir_head;
		cr->cur_cmd = cr->stack;
		if (cr->stack_head && cr->stack_head->type == e_t_pipe)
			cr->stack_head->right = cr->stack;
		else
			cr->stack_head = cr->stack;
	}
	lex->p_token = e_t_inf;
	return (0);
}

int	pipe_node(t_lexer *lex, t_node_creator *cr)
{
	if (!cr->stack_head && !cr->cur_cmd && !cr->redir_head)
	{
		ft_printf_err("minishell: syntax error near unexpected token `|'\n");
		*lst_rtn() = 2;
		return (1);
	}
	if (lex->p_token == e_t_pipe)
	{
		ft_printf_err("minishell: syntax error near unexpected token `|'\n");
		*lst_rtn() = 2;
		return (1);
	}
	if (!(cr->temp = create_new_node(e_t_pipe)))
		return (1);
	cr->temp->left = cr->stack_head;
	cr->stack_head = cr->temp;
	cr->stack = 0;
	cr->cur_cmd = 0;
	cr->redir_head = 0;
	cr->redir = 0;
	lex->p_token = e_t_pipe;
	return (0);
}
