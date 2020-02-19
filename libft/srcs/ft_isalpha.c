/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:42:37 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/17 11:05:09 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower1(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c);
	return (0);
}

static int	ft_isupper1(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c);
	return (0);
}

int			ft_isalpha(int c)
{
	if (ft_islower1(c) || ft_isupper1(c))
		return (c);
	return (0);
}
