/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/06 12:01:01 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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