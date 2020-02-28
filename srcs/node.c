/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:03:18 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/28 14:12:10 by cjaimes          ###   ########.fr       */
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
	return (node);
}

t_node	*generate_tree(t_lexer *lex)
{
	t_list *token;
	t_node *tree;
	t_node *stack;
	t_node *temp;
	t_node *stack_head;

	token = lex->tokens;
	tree = 0;
	stack = 0;
	stack_head = 0;
	while (token)
	{
		if (ft_strcmp(">", token->content) == 0)
		{
			// to handle later, for now is error
			break ;
		}
		if (ft_strcmp("<", token->content) == 0)
		{
			// to handle later, for now is error
			break ;
		}
		if (ft_strcmp(">>", token->content) == 0)
		{
			// to handle later, for now is error
			break ;
		}
		if (ft_strcmp("|", token->content) == 0)
		{
			// if tree and stack is null, throw parse error
			
		}
		if (ft_strcmp(";", token->content) == 0)
		{
			// if tree and stack is null, throw parse error
			if (!stack_head && !tree)
			{
				// throw error
				break ;
			}
			if (!(temp = create_new_node(e_t_semi_colon)))
					return (0);
			if (tree && tree->type == e_t_semi_colon)
			{
				temp->left = tree;
				tree->right = stack_head;
				tree = temp;
				stack_head = 0;
				stack = 0;
			}
			// else if (stack_head->type == e_t_semi_colon)
			// {
			// 	temp->left = stack_head;
			// 	//tree->right = stack_head;
			// 	tree = temp;
			// 	stack_head = 0;
			// 	stack = 0;
			// }
			else
			{
				temp->left = stack_head;
				tree = temp;
				stack = 0;
				stack_head = 0;
			}
		}
		else
		{
			if (!stack)
			{
				if (!(stack = create_new_node(e_t_cmd_name)))
					return (0);
				stack->content = token->content;
				stack_head = stack;
			}
			else
			{
				//printf("boo\n");
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
			}
		}
		token = token->next;
	}
	if (!tree && stack_head)
	{
		tree = stack_head;
		stack_head = 0;
	}
	if (stack_head)
		if (tree->type == e_t_semi_colon)
			tree->right = stack_head;
	return (tree);
}