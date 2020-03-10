/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/10 12:41:37 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_exec(t_lexer *lex, t_node *node)
{
	char	*path;
	char	*err;
	pid_t	pid;
	int		a;

	if((pid = fork()) == 0)
		if(node->right)
			handle_redir(lex, node->right);
	if (node->left)
	{
		if (!node->left->content || treat_word(lex, node->left) == FAILURE)
			return ;
		path = node->left->content;
		if (starts_with(path, "~"))
		{
			if (!(path = ft_strjoin(get_var(lex->env_list, "HOME")->value, path + 1)))
				return ;
			//printf("path is %s\n", path);
			//write(1, "he\n", 3);
			//printf("nani\n");
			free(node->left->content);
			//printf("nani2\n");
			//write(1, "ho\n", 3);
			node->left->content = path;
		}
		if (chdir(path) == -1)
		{
			err = strerror(errno);
			if (!pid)
			{
				ft_printf_err("minishell: cd: %s: %s\n", node->left->content, err);
				exit(EXIT_SUCCESS);
			}
			//return ;
		}
	}
	else
	{
		path = get_var(lex->env_list, "HOME")->value;
		chdir(path);
	}
	printf("nani5\n");
	if (pid)
		update_pwd(lex->env_list);
	printf("nani6\n");
	if (pid)
	{
		waitpid(pid, &a, 0);
	}
	else
		exit(EXIT_SUCCESS);
}
