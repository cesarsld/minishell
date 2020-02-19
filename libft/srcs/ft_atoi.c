/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:04:12 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/08 11:56:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		sign = (*str++ == '-');
	while (*str)
		if (*str >= '0' && *str <= '9')
			nb = nb * 10 + *str++ - '0';
		else
			break ;
	if (sign)
		return ((int)(-nb));
	return ((int)nb);
}
