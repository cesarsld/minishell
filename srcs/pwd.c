/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:18:17 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/09 17:39:42 by cjaimes          ###   ########.fr       */
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

void	pwd_error(void)
{
	ft_putstr("pwd: too many arguments");
	return ;
}

int		update_pwd(t_list *env_list)
{
	t_var *pwd_var;
	t_var *old_pwd_var;

	if (!(pwd_var = get_var(env_list, "PWD")))
		return (0);
	if (!(old_pwd_var = get_var(env_list, "OLDPWD")))
		return (0);
	free(old_pwd_var->value);
	old_pwd_var->value = pwd_var->value;
	pwd_var->value = get_pwd();
	return (1);
}