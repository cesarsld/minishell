/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/08 13:42:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_to_home(char *path, pid_t pid, t_lexer *lex)
{
	t_var *var;

	var = get_var(lex->env_list, "HOME");
	if (var)
		path = var->value;
	else if (!pid)
	{
		ft_printf_err("minishell: cd: HOME not set\n");
		exit(FAILURE);
	}
	if (chdir(path) == -1 && !pid)
	{
		ft_printf_err("minishell: cd: %s: %s\n", path, strerror(errno));
		exit(FAILURE);
	}
}

char	*cd_to_path(t_node *node, pid_t pid, t_lexer *lex)
{
	char	*temp;
	char	*path;

	temp = 0;
	if (!node->left->content || treat_word(lex, node->left) == FAILURE)
		return (0);
	path = ft_strdup(node->left->content);
	if (!path)
		return (0);
	if (starts_with(path, "~"))
	{
		if (!(temp = ft_strjoin(lex->home, path + 1)))
			return (0);
		free(path);
		path = temp;
	}
	if (chdir(path) == -1 && !pid)
	{
		ft_printf_err("minishell: cd: %s: %s\n", path, strerror(errno));
		exit(FAILURE);
	}
	return (path);
}

void	cd_exec(t_lexer *lex, t_node *node)
{
	char	*path;
	pid_t	pid;
	int		a;

	path = 0;
	if ((pid = fork()) == 0)
		if (node->right)
			handle_redir(lex, node->right);
	if (node->left)
	{
		path = cd_to_path(node, pid, lex);
		if (!path)
			return ;
	}
	else
		cd_to_home(path, pid, lex);
	update_pwd(lex, path, pid);
	free(path);
	if (pid)
	{
		waitpid(pid, &a, 0);
		*lst_rtn() = WIFEXITED(a) ? WEXITSTATUS(a) : *lst_rtn();
	}
	else
		exit(EXIT_SUCCESS);
}
