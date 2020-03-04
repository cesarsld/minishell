/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:00:56 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/11 15:14:57 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

char	*tab_zero(char *res, char *base)
{
	res[0] = base[0];
	return (res);
}

void	set_zero(char *tab, int len)
{
	while (len--)
		*tab++ = 0;
}

char	*ft_itoa_base_u(unsigned long long num, char *res,
						char *base, int is_neg)
{
	int		tab[256];
	int		a;
	int		length;

	length = ft_strlen(base);
	a = 0;
	set_zero(res, 25);
	if (num == 0)
		return (tab_zero(res, base));
	while (num > 0)
	{
		tab[a++] = num % length;
		num /= length;
	}
	if (is_neg)
		res[num++] = '-';
	while (a-- > 0)
		res[num++] = base[tab[a]];
	res[num] = 0;
	return (res);
}

void	get_base(long long int num, t_conv *conv)
{
	char				res[25];
	unsigned long long	i;

	if (num < 0)
		i = num * -1;
	else
		i = num;
	ft_itoa_base_u(i, res, "0123456789", num < 0 ? 1 : 0);
	append_string(conv, res);
}

void	get_base_u(unsigned long long num, t_conv *conv, char arg)
{
	char res[25];

	if (arg == 'b')
		ft_itoa_base_u(num, res, "01", 0);
	else if (arg == 'o')
		ft_itoa_base_u(num, res, "01234567", 0);
	else if (arg == 'd' || arg == 'i' || arg == 'u')
		ft_itoa_base_u(num, res, "0123456789", 0);
	else if (arg == 'x' || arg == 'p')
		ft_itoa_base_u(num, res, "0123456789abcdef", 0);
	else if (arg == 'X')
		ft_itoa_base_u(num, res, "0123456789ABCDEF", 0);
	append_string(conv, res);
	if (arg == 'p')
		prepend_string(conv, "0x");
}
