/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:05:03 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/17 11:08:27 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy1(char *dst, const char *src, size_t n)
{
	int i;

	i = n;
	while (n != 0)
	{
		if (*src)
			*dst = *src++;
		else
			*dst = '\0';
		dst++;
		n--;
	}
	return (dst - i);
}

static char	**create_tab(int count, const char *str, char c)
{
	char		**tab;
	int			i;
	const char	*cpy;

	if (!(tab = malloc((count + 1) * sizeof(char*))))
		return (NULL);
	while (*str && !(i = 0))
	{
		while (*str == c)
			str++;
		cpy = str;
		if (*str)
		{
			while (*str && *str++ != c)
				i++;
			if (!((*tab) = ft_calloc((i + 1) * sizeof(char), 1)))
				return (NULL);
			*tab = ft_strncpy1(*tab, cpy, i);
			tab++;
		}
	}
	*tab = 0;
	return (tab - count);
}

char		**ft_split(char const *s, char c)
{
	int			count;
	const char	*cpy;

	if (!s)
		return (NULL);
	cpy = s;
	count = 0;
	while (*cpy)
	{
		while (*cpy == c && *cpy)
			cpy++;
		if (*cpy)
		{
			while (*cpy && *cpy != c)
				cpy++;
			count++;
		}
	}
	return (create_tab(count, s, c));
}
