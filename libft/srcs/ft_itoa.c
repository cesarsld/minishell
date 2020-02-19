/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:00:54 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/17 11:05:32 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*string_zero(void)
{
	char *res;

	if (!(res = malloc(2 * sizeof(char))))
		return (NULL);
	*res = '0';
	res[1] = 0;
	return (res);
}

char		*ft_itoa(int n)
{
	char	tab[11];
	char	*res;
	int		sign;
	int		i;
	int		j;

	if (n == 0)
		return (string_zero());
	j = 0;
	i = 0;
	sign = n < 0 ? -1 : 1;
	while (n != 0)
	{
		tab[i++] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	if (sign == -1)
		tab[i++] = '-';
	if (!(res = malloc((i + 1) * sizeof(char))))
		return (NULL);
	res[i] = 0;
	while (i-- > 0)
		res[j++] = tab[i];
	return (res);
}
