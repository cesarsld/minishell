/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/22 15:50:12 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_exec(t_lexer *lex, t_node *node)
{
	char	*path;
	char	*err;
	char	*temp;
	pid_t	pid;
	int		a;

	temp = 0;
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
			if (!(temp = ft_strjoin(get_var(lex->env_list, "HOME")->value, path + 1)))
				return ;
			path = temp;
		}
		if (chdir(path) == -1)
		{
			err = strerror(errno);
			if (!pid)
			{
				ft_printf_err("minishell: cd: %s: %s\n", path, err);
				exit(EXIT_SUCCESS);
			}
		}
	}
	else
	{
		path = get_var(lex->env_list, "HOME")->value;
		if (chdir(path) == -1)
		{
			err = strerror(errno);
			if (!pid)
			{
				ft_printf_err("minishell: cd: %s: %s\n", path, err);
				exit(EXIT_SUCCESS);
			}
		}
	}
	free(temp);
	if (pid)
		update_pwd(lex->env_list, path);
	if (pid)
		waitpid(pid, &a, 0);
	else
		exit(EXIT_SUCCESS);
}
