/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:03:18 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 03:43:12 by cjaimes          ###   ########.fr       */
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

int		is_redir(const char *redir, char *token)
{
	int len;

	if (ft_strcmp(redir, token) == 0)
		return (1);
	len = ft_strlen(token);
	if (token[len - 1] == *redir && is_number_n(token, len - 1))
		return (1);
	return (0);
}

void	init_cr(t_node_creator *cr)
{
	cr->cur_cmd = 0;
	cr->stack = 0;
	cr->stack_head = 0;
	cr->redir = 0;
	cr->redir_head = 0;
}

int		handle_end(t_lexer *lex, t_node_creator *cr)
{
	if (!lex->tree && !cr->stack_head)
		return (0);
	if (!lex->tree && cr->stack_head)
	{
		lex->tree = cr->stack_head;
		cr->stack_head = 0;
	}
	if (cr->stack_head && lex->tree->type == e_t_semi_colon)
	{
		lex->tree->right = cr->stack_head;
		cr->stack = 0;
	}
	if (lex->p_token == e_t_supp || lex->p_token == e_t_d_supp ||
		lex->p_token == e_t_inf || lex->p_token == e_t_pipe)
	{
		ft_printf_err("minishell: syntax error near unexpected token `%s'\n",
			lex->p_token == e_t_pipe ? "|" : "newline");
		return (1);
	}
	if (lex->tree->type == e_t_semi_colon && cr->stack)
		lex->tree->right = cr->stack;
	return (0);
}

int		generate_tree(t_lexer *lex)
{
	t_list			*token;
	t_node_creator	cr;

	init_cr(&cr);
	token = lex->tokens;
	while (token)
	{
		if (handle_first(token, lex, &cr))
			return (1);
		token = token->next;
	}
	return (handle_end(lex, &cr));
}
