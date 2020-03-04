/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:52 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/08 17:54:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_prefix_ox(t_conv *conv, char arg)
{
	int pre;

	pre = 0;
	if (!conv->options.prefix)
		return (pre);
	if (arg == 'o')
	{
		if (*(conv->stream) != '0')
			pre = prepend_string(conv, "0");
	}
	else if (arg == 'b' && *(conv->stream) != '0')
		pre = prepend_string(conv, "0b");
	else if (arg == 'x' && *(conv->stream) != '0')
		pre = prepend_string(conv, "0x");
	else if (arg == 'X' && *(conv->stream) != '0')
		pre = prepend_string(conv, "0X");
	return (pre);
}

void	handle_signed(t_conv *conv, char arg)
{
	if (!conv->options.signed_)
		return ;
	if (arg == 'd' || arg == 'i')
		if (*(conv->stream) != '-')
			prepend_string(conv, "+");
}

void	handle_blank(t_conv *conv, char arg)
{
	if (!conv->options.blank || conv->options.signed_)
		return ;
	if (arg == 'd' || arg == 'i')
		if (*(conv->stream) != '-')
			prepend_string(conv, " ");
}
