/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:18:17 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/31 16:06:03 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *get_pwd(void)
{
    char *path_name;

    path_name = NULL;
    path_name = getcwd(path_name, 0);
    return (path_name);
}

void    pwd_error(void)
{
    ft_putstr("pwd: too many arguments");
    return ;
}