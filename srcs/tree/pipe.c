/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:42:54 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:25:10 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pipe(void)
{
	perror("pipe");
	exit(FAILURE);
}

void	exit_fork(void)
{
	perror("fork");
	exit(FAILURE);
}

void	execute_pipe(t_node *tree, t_lexer *lex, int out_fd)
{
	int pfd[2];
	int pid_left;
	int pid_right;

	pipe(pfd) == -1 ? exit_pipe() : 0;
	if ((pid_right = fork()) == -1)
		exit_fork();
	if (pid_right == 0)
		return (handle_right_pipe(out_fd, pfd, lex, tree));
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (tree->left->type == e_t_cmd_name)
	{
		if ((pid_left = fork()) < 0)
			exit_fork();
		if (pid_left == 0)
			return (handle_left_pipe(pfd, lex, tree));
		end_pipe_flow(pfd, pid_left, pid_right);
	}
	else
		handle_new_pipe(pfd, pid_right, lex, tree);
}
