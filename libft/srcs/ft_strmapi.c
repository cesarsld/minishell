/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 12:29:24 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/08 12:49:12 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	char			*start;
	unsigned int	i;

	if (!s || !f || !(new = malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	start = new;
	while (*s)
		*new++ = f(i++, *s++);
	*new = 0;
	return (start);
}
