/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:24:09 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/07 10:48:12 by cjaimes          ###   ########.fr       */
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

char **generate_arguments(t_lexer *lex, t_node *args)
{
	char **arg_list;

	if (!(arg_list = malloc(sizeof(char*) * (count_args(args) + 1))))
		return (0);
	arg_list[count_args(args)] = 0;
	fill_args(lex, args, arg_list, 0);
	return (arg_list);
}

void handle_d_supp_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (perror("open()"));

	if (node->left)
	{
		close(fd);
		return (handle_redir(lex, node->left));
	}
	dup2(fd, STDOUT_FILENO);
}

void handle_supp_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (perror("open()"));

	if (node->left)
	{
		close(fd);
		return (handle_redir(lex, node->left));
	}
	dup2(fd, STDOUT_FILENO);
}

void handle_inf_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_RDONLY)) == -1)
	{
		ft_printf("minishell: %s: %s", strerror(errno), node->content);
		return ;
	}
	if (node->left)
	{
		close(fd);
		return (handle_redir(lex, node->left));
	}
	dup2(fd, STDIN_FILENO);
}

void handle_redir(t_lexer *lex, t_node *node)
{
	if (treat_word(lex, node) == FAILURE)
		exit(1);
	if (node->type == e_t_supp)
		handle_supp_redir(lex, node);
	else if (node->type == e_t_inf)
		handle_inf_redir(lex, node);
	else if (node->type == e_t_d_supp)
		handle_d_supp_redir(lex, node);
}

void	execute_command(t_node *cmd_node, t_lexer *lex)
{
	char	**args;
	char	*ex_name;

	if(cmd_node->right)
		handle_redir(lex, cmd_node->right);
	if (treat_word(lex, cmd_node) == FAILURE)
		exit(1);
	if (starts_with(cmd_node->content, "./"))
	{
		if (!(args = generate_arguments(lex, cmd_node)))
			exit(1);
		if (!(ex_name = ft_strdup(cmd_node->content)))
			exit(1);
		pop_word(ex_name, 2);
	}
	else
	{
		if (!(args = generate_arguments(lex, cmd_node)))
			exit(1);
		if (!(ex_name = get_command_path(get_var(lex->env_list, "PATH")->value, cmd_node->content)))
			exit(1);
	}
	execve(ex_name, args, lex->envac);
	ft_printf("execve failed\n");
	exit(1);
}

void	execute_pipe(t_node *tree, t_lexer *lex, int out_fd)
{
    int status;
	int pfd[2];
    int pid_left, pid_right;

    if (pipe(pfd) == -1) // create pipe
    {
        perror("pipe");
        exit(1);
    }
	if ((pid_right = fork()) == -1) //create right fork child
    	{
        	perror("fork");
        	exit(1);
    	}
    if (pid_right == 0)		// executes if in right child
	{
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO); //bind output to out_fd which would be input of superior level or 1 if level 0
        dup2(pfd[0], STDIN_FILENO); // bind input to end of pipe
    	close(pfd[1]);				// ignore pipe pipe entry
    	return (execute_command(tree->right, lex)); //right child end
   	}
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (tree->left->type == e_t_cmd_name) // if left side is cmd, we are in deepest level
	{
    	if ((pid_left = fork()) < 0) //fork left child
    	{
    	    perror("fork");
    	    exit(1);
    	}
   		if (pid_left == 0) // executes if in left child
    	{
    	    dup2(pfd[1], STDOUT_FILENO);	// bind output to pipe entry
			close(pfd[0]);					// close end of pipe as left child sends output to right child
    	    return (execute_command(tree->left, lex)); // left child end
    	}
		// we are in parent process, child will never reach this line,  ENF OF FLOW 
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid_left, &status, 0);
		waitpid(pid_right, &status, 0);
	}
	else // left is a pipe
	{
		close(pfd[0]); // close end of pipe data lost
		execute_pipe(tree->left, lex, pfd[1]); // recursion
		waitpid(pid_right, &status, 0);
	}
}

void	execute_tree(t_lexer *lex, t_node *node)
{
	pid_t	new_id;
	int		a;

	if (!node)
		return ;
	if (node->type == e_t_semi_colon)
	{
		execute_tree(lex, node->left);
		execute_tree(lex, node->right);
	}
	else if (node->type == e_t_cmd_name)
	{
		if((new_id = fork()) == 0)
			execute_command(node, lex);
		else
			waitpid(new_id, &a, 0);
	}
	if (node->type == e_t_pipe)
		return (execute_pipe(node, lex, STDOUT_FILENO));
}
