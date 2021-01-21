/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:21:00 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/21 01:08:59 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = ft_strlen(src);
	if (!dst || !src)
		return (0);
	while (i + 1 < dstsize && *src)
	{
		*dst++ = *src++;
		i++;
	}
	if (dstsize)
		*dst = '\0';
	return (n);
}
