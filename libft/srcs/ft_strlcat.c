/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:46:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/15 15:40:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		size_dest;
	size_t		size_src;

	size_dest = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (dstsize <= size_dest)
		return (dstsize + size_src);
	dstsize = dstsize - size_dest - 1;
	dst += size_dest;
	while (*src)
		if (dstsize--)
			*dst++ = *src++;
		else
			break ;
	*dst = 0;
	return (size_dest + size_src);
}
