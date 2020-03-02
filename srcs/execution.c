/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:24:09 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/02 18:19:23 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_node *args)
{
	if (args->left)
		return (count_args(args->left) + 1);
	else
		return (0);
}

void	fill_args(t_node *args, char **list, int level)
{
	if (args->left)
		fill_args(args->left, list, level + 1);
	if (args->content);
		list[level] = args->content;
}

char **generate_arguments(t_node *args)
{
	char **arg_list;

	if (!(arg_list = malloc(sizeof(char*) * (count_args(args) + 1))))
		return (0);
	arg_list[count_args(args)] = 0;
	fill_args(args, arg_list, 0);
	return (arg_list);
}

void	execute_tree(t_lexer *lex)
{
	t_node *tree;

	tree = lex->tree;
	if (tree->type == e_t_cmd_name)
		if (starts_with(tree->content, "./"))
		{
			
		}

}