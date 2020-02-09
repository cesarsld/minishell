/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:04:32 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/09 18:31:30 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Need to add more parsing
*/
int add_var(t_list *env_list, char *input)
{
	t_var   *new;
	t_list	*temp;
	t_list	*exist;
	char	*name;
	char	*value;

	if (!(name = ft_strndup(input, ft_strchr(input, '=') - input)))
			return (0);
	if (!(value = ft_strdup(ft_strchr(input, '=') + 1)))
			return (0);
	if (!(new = new_env(name, value, 1)))
		return (0);
	if (!(temp = ft_lstnew(new)))
		return (0);
	if ((exist = get_var(env_list, name)))
	{
		free(exist->content);
		exist->content = new;
	}
	else
		ft_lstadd_back(&env_list, temp);
	return (1);
}