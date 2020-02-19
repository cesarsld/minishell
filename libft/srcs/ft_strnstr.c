/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:01:40 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/17 11:06:55 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_needle(const char *haystack, const char *needle, size_t len)
{
	while (*haystack && *needle && len-- != 0)
		if (*haystack++ != *needle++)
			return (0);
	if (!*needle)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len != 0)
	{
		if (*haystack == *needle)
			if (check_needle(haystack, needle, len))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
