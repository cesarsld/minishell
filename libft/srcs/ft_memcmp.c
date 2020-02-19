/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 02:03:49 by cjaimes           #+#    #+#             */
/*   Updated: 2019/07/26 02:18:06 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *us1;
	const unsigned char *us2;

	us1 = s1;
	us2 = s2;
	while (n-- != 0)
		if (*us1++ != *us2++)
			return ((int)*--us1 - (int)*--us2);
	return (0);
}
