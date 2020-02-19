/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 12:59:00 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/16 18:06:47 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	true_len;

	if (!s)
		return (NULL);
	true_len = ft_strlen(s);
	if (start >= true_len)
		len = 0;
	if (true_len < len)
		len = true_len;
	if (!(new = malloc((len + 1) * sizeof(char))))
		return (NULL);
	new[len] = 0;
	while (len-- != 0)
		new[len] = s[start + len];
	return (new);
}
