/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:45:38 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/11 14:51:46 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = malloc((len + 2) * sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len + 2);
	ft_strlcat(new, "/", len + 2);
	ft_strlcat(new, s2, len + 2);
	return (new);
}

void	free_split(char **split)
{
	char **copy;

	copy = split;
	while (*split)
		free(*split++);
	free(*split);
	free(copy);
}

char	*check_path(char *command)
{
	struct stat	buf;
	
	is_dir(command);
	if (stat(command, &buf) == 0)
		return (command);
	ft_printf_err("minishell: %s: No such file or directory\n", command);
	return (0);
}

char	*get_command_path(char *path_line, char *command)
{
	char		**paths;
	char		**copy;
	struct stat	buf;
	char		*full;

	//if (starts_with(command, "/"))	
	//	return check_path(command);
	if (!(paths = ft_split(path_line, ':')))
		return (0);
	copy = paths;
	while (*paths)
	{
		full = ft_strjoin_path(*paths, command);
		if (stat(full, &buf) == 0)
		{
			free_split(copy);
			return (full);
		}
		free(full);
		paths++;
	}
	free_split(copy);
	ft_printf_err("minishell: %s: command not found\n", command);
	return (0);
}