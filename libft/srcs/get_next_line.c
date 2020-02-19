/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:13:31 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/22 12:37:47 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	scan_buf(char **line, char *buf, ssize_t size, int check)
{
	int i;

	i = 0;
	if (size == -1)
		return (-1);
	if ((i = check_line(line, buf, size)) == -1)
		return (-1);
	if (buf[i] == '\n')
		return (shift_buf(buf, i + 1, size, 0));
	if ((!size && **line))
		return (shift_buf(buf, i + 1, size, check));
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		size;
	int			ret;
	int			check;

	if (fd < 0 || !(*line = malloc(sizeof(char))) || BUFFER_SIZE <= 0)
		return (-1);
	(*line)[0] = 0;
	size = 1;
	while (size > 0)
	{
		check = 0;
		if ((size = ft_strlen(buf)) == 0)
		{
			size = read(fd, buf, BUFFER_SIZE);
			check = 1;
		}
		if ((ret = scan_buf(line, buf, size, check)) < 2)
			return (ret);
	}
	return (0);
}
