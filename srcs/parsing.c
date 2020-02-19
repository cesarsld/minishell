/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:29:41 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/19 13:09:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_error(char *err)
{
	ft_putstr("Error\n");
	ft_putstr(err);
	ft_putstr("\n");
	return (0);
}

int		print_ouput(char *out)
{
	ft_putstr(out);
	ft_putstr("\n");
	return (1);
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


char	*get_next_word(char **input, char *q_type)
{
	int count;
	char *first;
	char *word;
	char *new_input;
	char *temp;
	char cur;

	cur = 0;
	count = 0;
	temp = 0;
	new_input = 0;
	first = *input;
	// 'e'\"c\"\"\"'ho'\" boo
	while (**input)
	{
		if ((**input == '\'' || **input == '"') && !cur)
			cur = **input;
		else if ((**input == '\'' || **input == '"') && **input  == cur)
			cur = 0;
		if (is_white_space(*(*input)++) && !cur)
			break ;
		count++;
	}
	if (!(word = ft_strndup(first, count)))
		return (0);
	if (cur)
	{
		*q_type = 0;
		ft_putstr("> ");
		if (!get_next_line(0, &new_input))
	 		return (0);
		if (!(temp = ft_strjoin_input(word, new_input)))
			return (0);
		free(new_input);
		free(word);
		free(first);
		*input = temp;
		return (get_next_word(input, q_type));
	}
	return (word);
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
	//*(line + index + i) = 0;
}

void filter_word(char *word)
{
	int front;
	int counter;
	char cur;

	cur = 0;
	counter = 0;
	front = -1;
	while (*word)
	{
		if ((*word == '\'' || *word == '"'))
		{
			if (!cur)
				cur = *word;
			if (front == -1)
				front = counter;
			else if (*word == cur)
			{
				shift_from_index(word - counter, front);
				shift_from_index(word - 1, 0);
				word -= 2;
				counter -= 2;
				front = -1;
				cur = 0;
				continue;
			}
		}
		word++;
		counter++;
	}
}

t_list *lex_parse_line(char **line)
{
	char *word;
	char open;
	//char *user_input;
	
	open = 0;
	if (!(word = get_next_word(line, &open)))
		return (0);
	// if (open)
	// {
	// 	ft_putstr("> ");
	// 	if (!get_next_line(0, &user_input))
	//  		return (0);
		
	// }
	filter_word(word);
	printf("%s\n", word);
	return 0;
}