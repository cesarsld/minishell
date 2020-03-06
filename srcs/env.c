/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:55:04 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 18:34:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env_var(void *content)
{
	t_var *var;

	var = content;
	if (var->is_env)
	{
		ft_putstr(var->name);
		ft_putstr("=");
		ft_putstr(var->value);
		ft_putstr("\n");
	}
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

void    print_env_vars(t_list *env_list)
{
	ft_lstiter(env_list, &print_env_var);
}

void	env_error()
{
	ft_putstr("env: no arguments or options allowed\n");
}
