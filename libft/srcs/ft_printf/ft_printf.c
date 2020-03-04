/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:26:59 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/11 18:15:03 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_options(t_flag_options *options)
{
	options->prefix = 0;
	options->zero_pad = 0;
	options->left_pad = 0;
	options->blank = 0;
	options->signed_ = 0;
	options->grouping = 0;
	options->width = -1;
	options->prec = -1;
}

t_conv	*init_conv(void)
{
	t_conv	*conv;

	if (!(conv = malloc(sizeof(t_conv))))
		return (0);
	if (!(conv->stream = ft_strnew(OUTPUT_INTERVAL)))
		return (0);
	conv->length = 0;
	conv->buf_len = 0;
	conv->ret = 0;
	conv->max = OUTPUT_INTERVAL;
	return (conv);
}

void	free_obj(t_conv *conv)
{
	free(conv->stream);
	free(conv);
}

int		get_conv(t_conv *conv, va_list ap, const char **entry)
{
	if (**entry == '%')
	{
		init_options(&(conv->options));
		check_flags(entry, &(conv->options), ap);
		if (!check_length_modifiers(entry, conv, ap))
			return (0);
		flush_buffer(conv);
		flush_stream(conv);
	}
	else
		safe_strcat_char(conv, **entry);
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
		if (!get_conv(conv, ap, &entry))
			break ;
	flush_buffer(conv);
	ret = conv->ret;
	free_obj(conv);
	va_end(ap);
	return (ret);
}
