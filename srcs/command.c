/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:45:38 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/01 14:59:48 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *path_line, char *command)
{
	char **paths;

	if (!(paths = ft_split(path_line, ':')))
		return (1);
	while (*paths)
	{
		;
	}
}