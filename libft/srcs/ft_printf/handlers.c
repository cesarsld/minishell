/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:37:03 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:30:36 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	lld_handler(const char **entry, t_conv *conv, va_list ap)
{
	(*entry) += 2;
	if (**entry == 'i' || **entry == 'd')
		get_base(va_arg(ap, signed long long int), conv);
	else if (**entry == 'b' || **entry == 'o'
			|| **entry == 'u' || **entry == 'x' || **entry == 'X')
		get_base_u(va_arg(ap, unsigned long long int), conv, **entry);
	else if (**entry == '%')
		safe_strcat_char_arg(conv, '%');
	return (flag_handler(conv, **entry));
}

int	ld_handler(const char **entry, t_conv *conv, va_list ap)
{
	(*entry) += 1;
	if (**entry == 'i' || **entry == 'd')
		get_base(va_arg(ap, long int), conv);
	else if (**entry == 'b' || **entry == 'o'
			|| **entry == 'u' || **entry == 'x' || **entry == 'X')
		get_base_u(va_arg(ap, unsigned long int), conv, **entry);
	else if (**entry == '%')
		safe_strcat_char_arg(conv, '%');
	return (flag_handler(conv, **entry));
}

int	hhd_handler(const char **entry, t_conv *conv, va_list ap)
{
	(*entry) += 2;
	if (**entry == 'i' || **entry == 'd')
		get_base((signed char)va_arg(ap, int), conv);
	else if (**entry == 'b' || **entry == 'o'
			|| **entry == 'u' || **entry == 'x' || **entry == 'X')
		get_base_u((unsigned char)va_arg(ap, int), conv, **entry);
	else if (**entry == '%')
		safe_strcat_char_arg(conv, '%');
	return (flag_handler(conv, **entry));
}

int	hd_handler(const char **entry, t_conv *conv, va_list ap)
{
	(*entry) += 1;
	if (**entry == 'i' || **entry == 'd')
		get_base((short)va_arg(ap, int), conv);
	else if (**entry == 'b' || **entry == 'o'
			|| **entry == 'u' || **entry == 'x' || **entry == 'X')
		get_base_u((unsigned short)va_arg(ap, int), conv, **entry);
	else if (**entry == '%')
		safe_strcat_char_arg(conv, '%');
	return (flag_handler(conv, **entry));
}

int	std_handler(const char **entry, t_conv *conv, va_list ap, int fd)
{
	int s_conv_err;

	s_conv_err = 1;
	if (**entry == 'i' || **entry == 'd')
		get_base(va_arg(ap, int), conv);
	else if (**entry == 'b' || **entry == 'o'
			|| **entry == 'u' || **entry == 'x' || **entry == 'X')
		get_base_u(va_arg(ap, unsigned int), conv, **entry);
	else if (**entry == 'c')
		safe_strcat_char_arg(conv, va_arg(ap, int));
	else if (**entry == 's')
		s_conv_err = safe_strcat_arg(conv, va_arg(ap, const char*));
	else if (**entry == 'p')
		get_base_u(va_arg(ap, unsigned long long), conv, **entry);
	else if (**entry == '%')
		safe_strcat_char_arg(conv, '%');
	else if (**entry)
	{
		safe_strcat_char(conv, **entry, fd);
		return (1);
	}
	if (!s_conv_err)
		return (0);
	return (flag_handler(conv, **entry));
}
