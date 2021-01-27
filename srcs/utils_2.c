/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:58:43 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:59:26 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_name_char(char c)
{
	return (ft_isalnum(c) || c ==  '_');
}

int		is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_whitespace(char **line)
{
	while (is_white_space(**line))
		(*line)++;
}

char	*ft_strjoin_input(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = malloc((len + 2) * sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len + 2);
	ft_strlcat(new, "\n", len + 2);
	ft_strlcat(new, s2, len + 2);
	return (new);
}

void shift_from_index(char *line, int index)
{
	int i;

	i = 0;
	while (*(line + index + i))
	{
		*(line + index + i) = *(line + index + i + 1);
		i++;
	}
}