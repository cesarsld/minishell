/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:03:18 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/27 19:04:30 by cjaimes          ###   ########.fr       */
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

void	generate_tree(t_lexer *lex)
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
		else
		{
			if (!stack)
			{
				if (!(stack = create_new_node(e_cmd_name)))
					return (0);
				stack->content = token->content;
				stack_head = stack;
			}
			else
			{
				if (stack->type == e_cmd_name)
				{
					if (!(temp = create_new_node(e_cmd_word)))
					return (0);
					temp->content = token->content;
					stack->left = temp;
					stack = stack->left;
				}
			}
			
			
		}
		
		token = token->next;
	}
}