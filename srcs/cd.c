/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/07 16:02:28 by cjaimes          ###   ########.fr       */
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
