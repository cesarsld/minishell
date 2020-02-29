/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:31:11 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/29 21:09:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number_n(char *input, int size)
{
	printf("inppput size is %d is %s\n", size, input);
	while (size-- < 0)
		if (!ft_isdigit(*input++))
			return (0);
	return (1);
}