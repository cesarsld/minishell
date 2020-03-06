/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:26:59 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:32:27 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_conv(t_conv *conv, va_list ap, const char **entry, int fd)
{
	if (**entry == '%')
	{
		init_options(&(conv->options));
		check_flags(entry, &(conv->options), ap);
		if (!check_length_modifiers(entry, conv, ap, fd))
			return (0);
		flush_buffer(conv, fd);
		flush_stream(conv, fd);
	}
	else
		safe_strcat_char(conv, **entry, fd);
	if (**entry)
		(*entry)++;
	return (1);
}

int		ft_printf(const char *entry, ...)
{
	va_list	ap;
	t_conv	*conv;
	int		ret;

	if (!(conv = init_conv()))
		return (0);
	va_start(ap, entry);
	while (*entry)
		if (!get_conv(conv, ap, &entry, 1))
			break ;
	flush_buffer(conv, 1);
	ret = conv->ret;
	free_obj(conv);
	va_end(ap);
	return (ret);
}

int		ft_printf_err(const char *entry, ...)
{
	va_list	ap;
	t_conv	*conv;
	int		ret;

	if (!(conv = init_conv()))
		return (0);
	va_start(ap, entry);
	while (*entry)
		if (!get_conv(conv, ap, &entry, 2))
			break ;
	flush_buffer(conv, 2);
	ret = conv->ret;
	free_obj(conv);
	va_end(ap);
	return (ret);
}
