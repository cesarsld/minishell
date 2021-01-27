/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:42:59 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 23:47:31 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_right_pipe(int out_fd, int pfd[2], t_lexer *lex, t_node *tree)
{
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO); //bind output to out_fd which would be input of superior level or 1 if level 0
	dup2(pfd[0], STDIN_FILENO); // bind input to end of pipe
	close(pfd[1]);				// ignore pipe pipe entry
	if(is_builtin(lex, tree->right) == SUCCESS)
		exit(1) ;
	return (execute_command(tree->right, lex, 0)); //right child end
}

void handle_left_pipe(int pfd[2], t_lexer *lex, t_node *tree)
{
	dup2(pfd[1], STDOUT_FILENO);	// bind output to pipe entry
	close(pfd[0]);					// close end of pipe as left child sends output to right child
	if(is_builtin(lex, tree->left) == SUCCESS)
		exit(1) ;
	return (execute_command(tree->left, lex, 0)); // left child end
}

void end_pipe_flow(int pfd[2], int pid_left, int pid_right)
{
	int status;
	// we are in parent process, child will never reach this line,  ENF OF FLOW 
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
}

void handle_new_pipe(int pfd[2], int pid_right, t_lexer *lex, t_node *tree)
{
	int status;
	
	close(pfd[0]); // close end of pipe data lost
	execute_pipe(tree->left, lex, pfd[1]); // recursion
	waitpid(pid_right, &status, 0);
}
