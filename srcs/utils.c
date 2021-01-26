/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:31:11 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:16:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number_n(char *input, int size)
{
	if (*input == '+' || *input == '-')
		input++;
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

int is_valid_assign_n(char *word, int len)
{
	while (len--)
		if (!is_name_char(*word++))
			return (0);
	return (1);
}

int contains_char(const char *input, char chr)
{
	while (*input)
		if (*input++ == chr)
			return (1);
	return (0);
}

int starts_with(const char *input, const char *match)
{
	return (ft_strncmp(input, match, ft_strlen(match)) == 0);  
}