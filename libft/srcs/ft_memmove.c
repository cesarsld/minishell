/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:39:25 by cjaimes           #+#    #+#             */
/*   Updated: 2019/07/26 01:59:03 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					gap;

	d = dst;
	s = src;
	gap = d - s;
	if (!gap)
		return (dst);
	if (gap > 0 && (size_t)(gap) < len)
		while (len-- != 0)
			d[len] = s[len];
	else
		while (len-- != 0)
			*d++ = *s++;
	return (dst);
}
