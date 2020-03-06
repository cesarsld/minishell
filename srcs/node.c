/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:03:18 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:07:55 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_new_node(t_oken_type type)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		return (0);
	node->content = 0;
	node->left = 0;
	node->right = 0;
	node->type = type;
	node->fd = -1;
	return (node);
}

int	is_redirection(const char *redir, char *token)
{
	int len;

	if (ft_strcmp(redir, token) == 0)
		return (1);
	len = ft_strlen(token);
	if (token[len - 1] == *redir && is_number_n(token, len - 1))
		return (1);
	return (0);
}

int	generate_tree(t_lexer *lex)
{
	t_list *token;
	t_node *stack;
	t_node *temp;
	t_node *stack_head;
	t_node *redir;
	t_node *redir_head;
	t_node *cur_cmd;

	cur_cmd = 0;
	token = lex->tokens;
	stack = 0;
	stack_head = 0;
	redir = 0;
	redir_head = 0;
	while (token)
	{
		if (is_redirection(">", token->content))
		{
			if (!(temp = create_new_node(e_t_supp)))
				return (0);
			temp->fd = get_number(token->content, ft_strlen(token->content) - 1);
			if (!redir_head)
			{
				redir_head = temp;
				redir = temp;
			}
			else 
			{
				redir->left = temp;
				redir = temp;
			}
			if (cur_cmd)
				cur_cmd->right = redir_head;
			lex->previous_token = e_t_supp;
		}
		else if (is_redirection("<", token->content))
		{
			if (!(temp = create_new_node(e_t_inf)))
				return (0);
			temp->fd = get_number(token->content, ft_strlen(token->content) - 1);
			if (!redir_head)
			{
				redir_head = temp;
				redir = temp;
			}
			else 
			{
				redir->left = temp;
				redir = temp;
			}
			if (cur_cmd)
				cur_cmd->right = redir_head;
			lex->previous_token = e_t_inf;
		}
		else if (is_redirection(">>", token->content))
		{
			if (!(temp = create_new_node(e_t_d_supp)))
				return (0);
			temp->fd = get_number(token->content, ft_strlen(token->content) - 1);
			if (!redir_head)
			{
				redir_head = temp;
				redir = temp;
			}
			else 
			{
				redir->left = temp;
				redir = temp;
			}
			if (cur_cmd)
				cur_cmd->right = redir_head;
			lex->previous_token = e_t_d_supp;
		}
		else if (ft_strcmp("|", token->content) == 0)
		{
			// if tree and stack is null, throw parse error
			if (!stack_head)
			{
				ft_putstr("minishell: syntax error near unexpected token `|'\n: ");
				break ;
			}
			if (!(temp = create_new_node(e_t_pipe)))
				return (0);
			temp->left = stack_head;
			stack_head = temp;
			stack = 0;
			cur_cmd = 0;
			redir_head = 0;
			redir_head = 0;
			lex->previous_token = e_t_pipe;
		}
		else if (ft_strcmp(";", token->content) == 0)
		{
			// if tree and stack is null, throw parse error
			if (!stack_head && !lex->tree)
			{
				// throw error
				ft_putstr("minishell: syntax error near unexpected token `;'\n: ");
				break ;
			}
			if (!(temp = create_new_node(e_t_semi_colon)))
					return (0);
			if (lex->tree && lex->tree->type == e_t_semi_colon)
			{
				temp->left = lex->tree;
				lex->tree->right = stack_head;
			}
			// else if (stack_head->type == e_t_semi_colon)
			// {
			// 	temp->left = stack_head;
			// 	//lex->tree->right = stack_head;
			// 	lex->tree = temp;
			// 	stack_head = 0;
			// 	stack = 0;
			// }
			else
			{
				temp->left = stack_head;
			}
			lex->tree = temp;
			stack_head = 0;
			stack = 0;
			cur_cmd = 0;
			redir_head = 0;
			redir_head = 0;
			lex->previous_token = e_t_semi_colon;
		}
		else
		{
			if (lex->previous_token == e_t_supp || lex->previous_token == e_t_inf || lex->previous_token == e_t_d_supp)
			{
				redir->content = token->content;
				lex->previous_token = e_t_word;
			}
			else if (!stack)
			{
				if (!(stack = create_new_node(e_t_cmd_name)))
					return (0);
				if (stack_head && stack_head->type == e_t_pipe)
					stack_head->right = stack;
				else
					stack_head = stack;
				stack->content = token->content;
				cur_cmd = stack;
				if (redir_head)
					cur_cmd->right = redir_head;
				lex->previous_token = e_t_cmd_name;
			}
			else
			{
				if (stack->type == e_t_cmd_name)
				{
					if (!(temp = create_new_node(e_t_cmd_word)))
					return (0);
					temp->content = token->content;
					stack->left = temp;
					stack = stack->left;
				}
				else if (stack->type == e_t_cmd_word)
				{
					if (!(temp = create_new_node(e_t_cmd_word)))
					return (0);
					temp->content = token->content;
					stack->left = temp;
					stack = stack->left;
				}
				lex->previous_token = e_t_cmd_word;
			}
		}
		token = token->next;
	}
	if (!lex->tree && stack_head)
	{
		lex->tree = stack_head;
		stack_head = 0;
	}
	if (stack_head)
		if (lex->tree->type == e_t_semi_colon)
			lex->tree->right = stack_head;
	return (1);
}
