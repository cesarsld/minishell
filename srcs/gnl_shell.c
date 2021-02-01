/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:19:43 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/01 10:13:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		scan_buf_shell(char **line, char *buf, ssize_t size)
{
	int i;

	i = 0;
	if (size == -1)
		return (-1);
	if ((i = check_line(line, buf, size)) == -1)
		return (-1);
	if (buf[i] == '\n')
		return (shift_buf(buf, i + 1, size, 0));
	if (ft_strlen(*line) == 0 && buf[i] == 0)
		return (0);
	return (3);
}

int		get_next_line_shell(int fd, char **line)
{
	ssize_t		size;
	int			ret;

	if (fd < 0 || !(*line = malloc(sizeof(char))) || BUFFER_SIZE <= 0)
		return (-1);
	(*line)[0] = 0;
	size = 1;
	while (1)
	{
		if ((size = ft_strlen(g_buf)) == 0)
			size = read(fd, g_buf, BUFFER_SIZE);
		if ((ret = scan_buf_shell(line, g_buf, size)) < 2)
			return (ret);
	}
	return (0);
}
