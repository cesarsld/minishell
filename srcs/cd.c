/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/07 12:37:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_exec(t_lexer *lex, t_node *node)
{
	char *path;
	char *err;

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
			free(node->left->content);
			node->left->content = path;
		}
		if (chdir(node->left->content) == -1)
		{
			err = strerror(errno);
			ft_printf_err("bash: cd: %s: %s\n", node->left->content, err);
			return ;
		}
	}
	else
	{
		path = get_var(lex->env_list, "HOME")->value;
		chdir(path);
	}
	update_pwd(lex->env_list);
}

int		get_cd(const char *dir, t_list *env_list)
{
	char *query;

	query = 0;
	if (starts_with(dir, "~"))
		if (!(query = ft_strjoin(get_var(env_list, "HOME")->value, dir + 1)))
			return (0);
	if (query)
		return (chdir(query));
	return (chdir(dir));
}

void	cd_error(const char *dir)
{
	ft_putstr("cd: no such file or directory : ");
	ft_putstr(dir);
	ft_putstr("\n");
}

void	cd_pwd_error(char *dir)
{
	char *copy;

	copy = dir;
	while (*copy)
	{
		if (!is_white_space(*copy))
			copy++;
		else
		{
			*copy = 0;
			break ;
		}   
	}
	ft_putstr("cd: string not in pwd : ");
	ft_putstr(dir);
	ft_putstr("\n");
}

void	cd_dir_error(char * err, const char *dir)
{
	ft_putstr("cd: ");
	ft_putstr(err);
	ft_putstr(": ");
	ft_putstr(dir);
	ft_putstr("\n");
}