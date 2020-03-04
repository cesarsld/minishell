/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:17:00 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/11 18:04:41 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	zero_precision_case(t_conv *conv, char arg)
{
	if (!conv->options.prec)
	{
		if (arg == 'b' || arg == 'u' || arg == 'x'
			|| arg == 'X' || arg == 'd' || arg == 'i')
		{
			if (*(conv->stream) == '0' && conv->length == 1)
			{
				conv->length = 0;
				*(conv->stream) = 0;
				return (1);
			}
		}
		else if (arg == 'o')
		{
			if (!conv->options.prefix)
			{
				conv->length = 0;
				*(conv->stream) = 0;
			}
			return (1);
		}
	}
	return (0);
}

int	precision_handler(t_conv *conv, char arg, int pre)
{
	int neg;

	if (zero_precision_case(conv, arg))
		return (1);
	if (arg == 'd' || arg == 'i')
	{
		(neg = (*(conv->stream) == '-')) ? shift_left_string(conv, 1) : 0;
		if (conv->options.prec > conv->length)
			if (!left_pad(conv, conv->options.prec - conv->length, '0'))
				return (0);
		neg ? prepend_string(conv, "-") : 0;
	}
	if (arg == 'o' || arg == 'u' || arg == 'x' || arg == 'X' || arg == 'b')
		if (conv->options.prec > conv->length)
			if (!inject(conv, conv->options.prec - conv->length - pre,
				pre, '0'))
				return (0);
	if (arg == 's')
		if (conv->length > conv->options.prec && conv->options.prec >= 0)
			shave(conv, conv->options.prec);
	return (1);
}

int	width_handler(t_conv *conv, int pre)
{
	if (conv->length > conv->options.width)
		return (1);
	while (conv->options.width + 1 > conv->max)
		if (!inc_str_len(conv))
			return (0);
	if (conv->options.left_pad)
	{
		if (!right_pad(conv, conv->options.width - conv->length, ' '))
			return (0);
	}
	else
	{
		if (conv->options.zero_pad && conv->options.prec < 0)
		{
			if (!inject(conv, conv->options.width - conv->length,
			(*(conv->stream) == '-') || (*(conv->stream) == '+') ? 1 : pre,
			'0'))
				return (0);
		}
		else if (!left_pad(conv, conv->options.width - conv->length, ' '))
			return (0);
	}
	return (1);
}

int	flag_handler(t_conv *conv, char arg)
{
	int pre;

	pre = handle_prefix_ox(conv, arg);
	if (!precision_handler(conv, arg, pre))
		return (0);
	handle_signed(conv, arg);
	handle_blank(conv, arg);
	if (!width_handler(conv, pre))
		return (0);
	return (1);
}
