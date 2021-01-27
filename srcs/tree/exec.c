/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:52:11 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:21:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_args(t_node *args)
{
	if (args)
		return (count_args(args->left) + 1);
	else
		return (0);
}

void	fill_args(t_lexer *lex, t_node *args, char **list, int level)
{
	if (args)
		fill_args(lex, args->left, list, level + 1);
	if (args && args->content)
	{
		if (treat_word(lex, args) == FAILURE)
			exit(1);
		list[level] = args->content;
	}
}

char	**generate_arguments(t_lexer *lex, t_node *args)
{
	char **arg_list;

	if (!(arg_list = malloc(sizeof(char*) * (count_args(args) + 1))))
		return (0);
	arg_list[count_args(args)] = 0;
	fill_args(lex, args, arg_list, 0);
	return (arg_list);
}

void	execute_command(t_node *cmd_node, t_lexer *lex, char *ex_name)
{
	char	**args;

	if (cmd_node->right)
	{
		handle_redir(lex, cmd_node->right);
		!cmd_node->content ? exit(EXIT_SUCCESS) : 0;
	}
	if (!cmd_node->content)
		return ;
	if (treat_word(lex, cmd_node) == FAILURE ||
		!(args = generate_arguments(lex, cmd_node)))
		exit(FAILURE);
	if (ft_strchr(cmd_node->content, '/'))
	{
		if (!(ex_name = ft_strdup(cmd_node->content)) || is_dir(ex_name) == 1)
			exit(FAILURE);
	}
	else if (!(ex_name = get_command_path(
			get_var(lex->env_list, "PATH")->value, cmd_node->content)))
		exit(FAILURE);
	!get_env_list(lex) ? exit(FAILURE) : 0;
	execve(ex_name, args, lex->envac);
	ft_printf_err("minishell: %s: %s\n", cmd_node->content, strerror(errno));
	*lst_rtn() = 127;
	exit(errno);
}

void	handle_cmd_exec(t_lexer *lex, t_node *node)
{
	pid_t	new_id;
	int		a;

	if ((new_id = fork()) == 0)
		execute_command(node, lex, 0);
	else
	{
		waitpid(new_id, &a, 0);
		if (WIFEXITED(a))
			*lst_rtn() = WEXITSTATUS(a);
	}
}
