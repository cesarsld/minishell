/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:04:17 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:18:42 by cjaimes          ###   ########.fr       */
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

t_var	*new_env(char *name, char *value, int is_env)
{
	t_var *var;

	if (!(var = malloc(sizeof(t_var))))
		return (0);
	var->is_env = is_env;
	var->name = name;
	var->value = value;
	return (var);
}

t_list	*get_env_vars(char **env)
{
	t_list	*first;
	t_list	*temp;
	t_var	*var;
	char	*name_temp;
	char	*value_temp;

	first = 0;
	while (*env)
	{
		if (!(name_temp = ft_strndup(*env, ft_strchr(*env, '=') - *env)))
			return (0);
		if (!(value_temp = ft_strdup(ft_strchr(*env, '=') + 1)))
			return (0);
		if (!(var = new_env(name_temp, value_temp, 1)))
			return (0);
		if (!(temp = ft_lstnew(var)))
			return (0);
		ft_lstadd_back(&first, temp);
		env++;
	}
	return (first);
}
