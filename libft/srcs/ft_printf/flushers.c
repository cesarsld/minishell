/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flushers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:59:46 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:20:31 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flush_stream(t_conv *conv, int fd)
{
	int i;

	i = 0;
	write(fd, conv->stream, conv->length);
	conv->ret += conv->length;
	while (i < conv->max)
		conv->stream[i++] = 0;
	conv->length = 0;
}

void	flush_buffer(t_conv *conv, int fd)
{
	int i;

	i = 0;
	write(fd, conv->buffer, conv->buf_len);
	conv->ret += conv->buf_len;
	while (i < conv->buf_len)
		conv->buffer[i++] = 0;
	conv->buf_len = 0;
}
