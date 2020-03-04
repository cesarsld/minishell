/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:24:09 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/04 12:42:30 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_word(char *word, int amount)
{
	while (*(word + amount))
	{
		*word = *(word + amount);
		word++;
	}
	*word = 0;
}

int	count_args(t_node *args)
{
	if (args)
		return (count_args(args->left) + 1);
	else
		return (0);
}

void	fill_args(t_node *args, char **list, int level)
{
	//printf("content is %s\n", args->content);
	if (args)
		fill_args(args->left, list, level + 1);
	if (args && args->content)
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

void	execute_command(t_node *cmd_node, t_lexer *lex)
{
	char	**args;
	char	*ex_name;
	pid_t	new_id;
	int		a;

	if (starts_with(cmd_node->content, "./"))
	{
		if (!(args = generate_arguments(cmd_node)))
			return ; //malloc fail
		if (!(ex_name = ft_strdup(cmd_node->content)))
			return ;
		pop_word(ex_name, 2);
	}
	else
	{
		if (!(args = generate_arguments(cmd_node)))
			return ; //malloc fail
		if (!(ex_name = get_command_path(get_var(lex->env_list, "PATH")->value, cmd_node->content)))
			return ;
	}
	if((new_id = fork()) == 0)
		execve(ex_name, args, lex->envac);
	else
		waitpid(new_id, &a, 0);
}

void	execute_tree(t_lexer *lex)
{
	t_node	*tree;

	tree = lex->tree;
	if (tree && tree->type == e_t_cmd_name)
		execute_command(tree, lex);
}


void	execute_pipe()
{
	
}