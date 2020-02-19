/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:52:55 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/08 12:47:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*start;
	const unsigned char	*s;
	int					gap;

	gap = dst - src;
	if (gap < 0)
		gap = -gap;
	if ((size_t)gap < n)
		return (dst);
	s = src;
	start = dst;
	while (n-- > 0)
		*start++ = *s++;
	return (dst);
}
