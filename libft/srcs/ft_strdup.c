/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 11:06:25 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/10 17:03:51 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;
	char	*first;

	if (!(cp = malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (0);
	first = cp;
	while (*s1)
		*cp++ = *s1++;
	*cp = 0;
	return (first);
}
