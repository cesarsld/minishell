/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:06:40 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/08 17:43:19 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	shift_left_string(t_conv *conv, int offset)
{
	int		len;
	char	*str;

	str = conv->stream;
	len = conv->length;
	if (offset > len)
		offset = len;
	conv->length -= offset;
	while (*str)
	{
		*str = *(str + offset);
		if (!*(str + offset))
			--offset;
		str++;
	}
}

void	shift_right_string(char *str, int offset)
{
	int	len;

	len = ft_strlen(str);
	while (len--)
		str[len + offset] = str[len];
	while (offset--)
		str[offset] = 0;
}

int		left_pad(t_conv *conv, unsigned int amount, char pad)
{
	char *str;

	str = conv->stream;
	while (conv->length + (int)amount + 1 > conv->max)
		if (!inc_str_len(conv))
			return (0);
	shift_right_string(conv->stream, amount);
	conv->length += amount;
	while (amount--)
		*str++ = pad;
	return (1);
}

int		inject(t_conv *conv, unsigned int amount, int index, char cont)
{
	char *str;

	str = conv->stream + index;
	while (conv->length + (int)amount + 1 > conv->max)
		if (!inc_str_len(conv))
			return (0);
	shift_right_string(str, amount);
	conv->length += amount;
	while (amount--)
		*str++ = cont;
	return (1);
}

int		prepend_string(t_conv *conv, const char *pre)
{
	int		pre_len;
	char	*str;

	str = conv->stream;
	pre_len = ft_strlen(pre);
	shift_right_string(str, pre_len);
	while (*pre)
		*str++ = *pre++;
	conv->length += pre_len;
	return (pre_len);
}
