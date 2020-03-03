/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:31:11 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/01 17:33:55 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number_n(char *input, int size)
{
	while (size-- > 0)
		if (!ft_isdigit(*input++))
			return (0);
	return (1);
}

int	get_number(char *input, int size)
{
	if (!is_number_n(input, size))
		return (1);
	return (ft_atoi(input));
}