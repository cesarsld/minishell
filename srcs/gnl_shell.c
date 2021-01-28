/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:19:43 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/28 20:20:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		scan_buf_shell(char **line, char *buf, ssize_t size, int check)
{
	int i;

	i = 0;
	check = 0;
	if (size == -1)
		return (-1);
	if ((i = check_line(line, buf, size)) == -1)
		return (-1);
	if (buf[i] == '\n')
		return (shift_buf(buf, i + 1, size, 0));
	if(ft_strlen(*line) == 0 && buf[i] == 0)
		return (0);
	return (3);
}

int		get_next_line_shell(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		size;
	int			ret;
	int			check;

	if (fd < 0 || !(*line = malloc(sizeof(char))) || BUFFER_SIZE <= 0)
		return (-1);
	(*line)[0] = 0;
	size = 1;
	while (1)
	{
		check = 0;
		if ((size = ft_strlen(buf)) == 0)
		{
			size = read(fd, buf, BUFFER_SIZE);
			check = 1;
		}
		if ((ret = scan_buf_shell(line, buf, size, check)) < 2)
			return (ret);
	}
	return (0);
}
