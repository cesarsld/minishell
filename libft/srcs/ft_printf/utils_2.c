/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:33:47 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/08 17:43:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		inc_str_len(t_conv *conv)
{
	char *new;

	if (!(new = ft_strnew(conv->max * 2)))
		return (0);
	new = ft_strcat(new, conv->stream);
	free(conv->stream);
	conv->stream = new;
	conv->max *= 2;
	return (1);
}

void	append_string(t_conv *conv, const char *ap)
{
	int		len;
	char	*str;

	str = conv->stream;
	len = ft_strlen(ap);
	str += conv->length;
	while (*ap)
		*str++ = *ap++;
	conv->length += len;
}

void	shave(t_conv *conv, int offset)
{
	char *str;

	str = conv->stream;
	str += offset;
	while (*str)
		*str++ = 0;
	conv->length = offset;
}

int		right_pad(t_conv *conv, unsigned int amount, char pad)
{
	char *str;

	str = conv->stream;
	while (conv->length + (int)amount + 1 > conv->max)
		if (!inc_str_len(conv))
			return (0);
	conv->length += amount;
	while (amount--)
		*(--str + conv->length) = pad;
	return (1);
}
