/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:18:17 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/07 23:48:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char *path_name;

	path_name = NULL;
	path_name = getcwd(path_name, 0);
	return (path_name);
}

int		update_pwd(t_list *env_list)
{
	t_var *pwd_var;
	t_var *old_pwd_var;

	if (!(pwd_var = get_var(env_list, "PWD")))
		return (0);
	if ((old_pwd_var = get_var(env_list, "OLDPWD")))
	{
		free(old_pwd_var->value);
		old_pwd_var->value = pwd_var->value;
	}
	else
		free(pwd_var->value);
	if(!(pwd_var->value = ft_strdup(get_pwd())))
		return (0);
	return (1);
}

void pwd_exec(t_lexer *lex, t_node *node)
{
	pid_t	pid;
	int		a;

	if((pid = fork()) == 0)
	{
		if(node->right)
			handle_redir(lex, node->right);
	if (node->left)
	{
		ft_printf_err("bash: pwd: too many arguments or options\n");
		return ;
	}
		ft_printf("%s\n", get_pwd());
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &a, 0);
}