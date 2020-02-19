/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:35:39 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/17 11:07:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s, char const *set)
{
	size_t	len;
	char	*new;

	if (!s || !set)
		return (NULL);
	while (is_set(*s, set))
		s++;
	if (*s == 0)
	{
		if ((new = ft_calloc(sizeof(char), 1)))
			return (new);
		else
			return (NULL);
	}
	len = ft_strlen(s);
	while (is_set(s[len - 1], set))
		len--;
	if (!(new = ft_substr(s, 0, len)))
		return (NULL);
	return (new);
}
