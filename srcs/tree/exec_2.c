/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:25:54 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/08 19:26:07 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		count_sub_words(char *word)
{
	int count;

	count = 1;
	while (*word)
	{
		if (*word == ' ' && *(word + 1))
			count++;
		word++;
	}
	return (count);
}

int		expand_cmd(char **arg_list, char *word)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while(word[i])
	{
		if (word[i] == ' ')
		{
			if (!(arg_list[n] = ft_strndup(word, i)))
				return (-1);
			while (word[i] == ' ')
				i++;
			word += i;
			n++;
			i = -1;
		}
		i++;
	}
	
	if (i)
		if (!(arg_list[n++] = ft_strndup(word, i)))
			return (-1);
	return (!n ? 1 : n);
}
