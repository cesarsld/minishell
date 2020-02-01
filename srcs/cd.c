/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:42 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/01 14:10:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_cd(const char *dir)
{
    ft_putstr(dir);
    return (chdir(dir));
}

void cd_error(const char *dir)
{
    ft_putstr("cd: no such file or directory : ");
    ft_putstr(dir);
    ft_putstr("\n");
}

void cd_pwd_error(char *dir)
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

void cd_dir_error(char * err, const char *dir)
{
    ft_putstr("cd: ");
    ft_putstr(err);
    ft_putstr(": ");
    ft_putstr(dir);
    ft_putstr("\n");
}