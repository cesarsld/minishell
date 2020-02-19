/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:55:14 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/22 12:38:37 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpy_then_ncat(char *dst, char *src, char *cat, size_t n)
{
	char	*tmp;

	tmp = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	while (*cat && n--)
		*dst++ = *cat++;
	*dst = 0;
	return (tmp);
}

int			shift_buf(char *buf, int amount, ssize_t size, int check)
{
	int i;

	i = 0;
	buf[amount - 1] = 0;
	while (amount + i < BUFFER_SIZE + 0 && (buf[amount + i]))
	{
		buf[i] = buf[amount + i];
		buf[amount + i] = 0;
		++i;
	}
	if (check && !*buf)
		return (size == BUFFER_SIZE ? 1 : 0);
	return (1);
}

int			check_line(char **line, char *buf, int size)
{
	int		i;
	int		cont;
	char	*new;

	i = 0;
	while (i < size)
		if (buf[i] != '\n' && buf[i])
			i++;
		else
			break ;
	cont = ft_strlen(*line) + 1;
	if (!(new = malloc((cont + i) * sizeof(char))))
		return (-1);
	ft_cpy_then_ncat(new, *line, buf, i);
	free(*line);
	*line = new;
	cont = i;
	while (cont--)
		*buf++ = 0;
	return (i);
}
