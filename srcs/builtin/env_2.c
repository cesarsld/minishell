/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:04:17 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:06:27 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(t_list *env_list, char *key)
{
	t_var	*entry;
	
	while (env_list)
	{
		entry = env_list->content;
		if (ft_strcmp(key, entry->name) == 0)
			return (entry->value);
		env_list = env_list->next;
	}
	return (0);
}

t_var	*get_var(t_list *env_list, char *key)
{
	t_var *entry;
	
	while (env_list)
	{
		entry = env_list->content;
		if (ft_strcmp(key, entry->name) == 0)
			return (entry);
		env_list = env_list->next;
	}
	return (0);
}