/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:02:18 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 01:55:06 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_substr(char *start, int amount)
{
	while (*(start + amount))
	{
		*start = *(start + amount);
		start++;
	}
	*start = 0;
}
