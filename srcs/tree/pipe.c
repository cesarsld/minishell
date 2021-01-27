/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:42:54 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 23:54:54 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_pipe()
{
	perror("pipe");
	exit(FAILURE);
}

void exit_fork()
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

	if ((pid_right = fork()) == -1) //create right fork child
		exit_fork();
	if (pid_right == 0)		// executes if in right child
		return (handle_right_pipe(out_fd, pfd, lex, tree));
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (tree->left->type == e_t_cmd_name) // if left side is cmd, we are in deepest level
	{
		if ((pid_left = fork()) < 0) //fork left child
			exit_fork();
   		if (pid_left == 0) // executes if in left child
			return (handle_left_pipe(pfd, lex, tree));
		end_pipe_flow(pfd, pid_left, pid_right);
	}
	else // left is a pipe
		handle_new_pipe(pfd, pid_right, lex, tree);
}
