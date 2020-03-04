/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:19:55 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/11 14:34:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_precision(const char **entry, t_flag_options *options, va_list va)
{
	if (**entry == '.')
	{
		options->prec = 0;
		(*entry)++;
		if (**entry == '*')
		{
			(*entry)++;
			options->prec = va_arg(va, int);
			if (options->prec < 0)
				options->prec = 0;
			return (1);
		}
		while (**entry >= '0' && **entry <= '9')
			options->prec = options->prec * 10 + *(*entry)++ - '0';
	}
	return (1);
}

int		check_field_width(const char **entry,
							t_flag_options *options, va_list va)
{
	int width;

	width = 0;
	if (**entry == '*')
	{
		if ((width = va_arg(va, int)) < 0)
		{
			options->left_pad = 1;
			width *= -1;
		}
		(*entry)++;
	}
	else
	{
		if (**entry >= '1' && **entry <= '9')
			width = *(*entry)++ - '0';
		while (**entry >= '0' && **entry <= '9')
			width = width * 10 + *(*entry)++ - '0';
		if (!**entry)
			return (0);
	}
	options->width = width;
	return (check_precision(entry, options, va));
}

int		check_length_modifiers(const char **entry, t_conv *conv, va_list va)
{
	int res;

	res = 1;
	if (**entry == 'h')
	{
		if (*(*entry + 1) == 'h')
			res = hhd_handler(entry, conv, va);
		else
			res = hd_handler(entry, conv, va);
	}
	else if (**entry == 'l')
	{
		if (*(*entry + 1) == 'l')
			res = lld_handler(entry, conv, va);
		else
			res = ld_handler(entry, conv, va);
	}
	else
		res = std_handler(entry, conv, va);
	return (res);
}

int		check_flags(const char **entry, t_flag_options *options, va_list va)
{
	while (*++(*entry))
	{
		if (**entry == '#')
			options->prefix = 1;
		else if (**entry == '0')
			options->zero_pad = 1;
		else if (**entry == '-')
			options->left_pad = 1;
		else if (**entry == ' ')
			options->blank = 1;
		else if (**entry == '+')
			options->signed_ = 1;
		else if (**entry == '\'')
			options->grouping = 1;
		else
			return (check_field_width(entry, options, va));
	}
	return (0);
}
