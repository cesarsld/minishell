/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_appends.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:59:05 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:29:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		safe_strcat_char(t_conv *conv, unsigned char c, int fd)
{
	if (conv->buf_len + 1 == 4096 - 1)
		flush_buffer(conv, fd);
	conv->buffer[conv->buf_len++] = c;
	conv->buffer[conv->buf_len] = 0;
	return (1);
}

void	safe_strcat_char_arg(t_conv *conv, unsigned char c)
{
	conv->stream[conv->length++] = c;
	conv->stream[conv->length] = 0;
}

int		safe_strcat_arg(t_conv *conv, const char *str)
{
	int str_len;

	if (conv->options.prec == 0)
		return (1);
	if (!str)
	{
		append_string(conv, "(null)");
		return (1);
	}
	str_len = ft_strlen(str);
	while (conv->length + str_len + 1 > conv->max)
		if (!inc_str_len(conv))
			return (0);
	append_string(conv, str);
	return (1);
}
