/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:42:59 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:24:50 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_right_pipe(int out_fd, int pfd[2], t_lexer *lex, t_node *tree)
{
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	if (is_builtin(lex, tree->right) == SUCCESS)
		exit(1);
	return (execute_command(tree->right, lex, 0));
}

void	handle_left_pipe(int pfd[2], t_lexer *lex, t_node *tree)
{
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[0]);
	if (is_builtin(lex, tree->left) == SUCCESS)
		exit(1);
	return (execute_command(tree->left, lex, 0));
}

void	end_pipe_flow(int pfd[2], int pid_left, int pid_right)
{
	int status;

	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
}

void	handle_new_pipe(int pfd[2], int pid_right, t_lexer *lex, t_node *tree)
{
	int status;

	close(pfd[0]);
	execute_pipe(tree->left, lex, pfd[1]);
	waitpid(pid_right, &status, 0);
}
