/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:41:42 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/08 12:50:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char *s;

	d = dst;
	s = src;
	while (n-- != 0)
		if (*s == (unsigned char)c)
		{
			*d = *s;
			return ((void*)d + 1);
		}
		else
			*d++ = *s++;
	return (0);
}
