/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:24:09 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/04 15:47:36 by cjaimes          ###   ########.fr       */
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

void handle_supp_redir(t_node *node)
{
	int fd;
	char *line;


	line = 0;
	if (!(fd = open(node->content, O_CREAT | O_WRONLY)))
		return (perror("open()"));
	if (node->left)
	{
		close(fd);
		return (handle_supp_redir(node->left));
	}
	while (!get_next_line(node->fd, &line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		write(fd, line, ft_strlen(line));
	free(line);
}

void	execute_command(t_node *cmd_node, t_lexer *lex)
{
	char	**args;
	char	*ex_name;

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
	execve(ex_name, args, lex->envac);
}

void	execute_pipe(t_node *tree, t_lexer *lex)
{
    int status;
	int pfd[2];
    int pid_left, pid_right;

    if (pipe(pfd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    if ((pid_left = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid_left == 0)
    {
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[0]);
        close(pfd[1]);
        return (execute_tree(lex, tree->left));
    }
    if ((pid_right = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid_right == 0)
    {
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        close(pfd[1]);
        return (execute_tree(lex, tree->right));
    }
    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
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
		return (execute_pipe(node, lex));
}
