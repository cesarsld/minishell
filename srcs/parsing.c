/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:29:41 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/21 13:45:35 by cjaimes          ###   ########.fr       */
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
	int beg;

	beg = 0;
	cur = 0;
	count = 0;
	temp = 0;
	new_input = 0;
	first = *input;
	while (**input)
	{
		if ((**input == '\'' || **input == '"') && !cur)
		{
			beg = count;
			cur = **input;
		}
		else if ((**input == '\'' || **input == '"') && **input  == cur)
		{
			cur = 0;
		}
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

t_char	*create_sub_word(char *word)
{
	t_char *sub;

	if (!(sub = malloc(sizeof(t_char))))
		return (0);
	sub->value = word;
	return (sub);
}

void update_state(int *current, int *previous, int new)
{
	*previous= *current;
	*current = new;
}

t_list	*lex_it(char **input)
{
	int p_state;
	int state;
	int word_start;
	int counter;

	char *word;
	t_list *temp;
	t_list *list;

	list = 0;
	word = 0;
	word_start = -1;
	counter = 0;
	p_state = 0;
	state = e_general;
	while (**input)
	{
		printf("checking char `%c`\n", **input);
		if ((**input == '\'' || **input == '"') && (state == e_general || state == e_d_quote || state == e_s_quote))
		{
			if (state == e_general)
			{
				word_start = word_start == -1 ? counter: word_start;
				update_state(&state, &p_state, **input == '"' ? e_d_quote : e_s_quote);
			}
			else if ((state == e_d_quote && **input == '"') || (state == e_s_quote && **input == '\''))
			{
				update_state(&state, &p_state, e_general);
			}
			printf("state is %d\n", state);
		}
		else if (**input == '\\' && (state == e_d_quote || state == e_general || state == e_backslash))
		{
			if (state == e_backslash)
				update_state(&state, &p_state, p_state);
			else if (state == e_general)
			{
				if (word_start == -1)
					word_start = counter;
				update_state(&state, &p_state, e_backslash);
			}
			else
				update_state(&state, &p_state, e_backslash);
		}
		else if (is_white_space(**input) && state == e_general && word_start != -1)
		{	// word_start != -1 to check that we have started a word handles spree of white spaces
			if (!(word = ft_strndup(*input - counter + word_start, counter - word_start)))
				return (0);
			//printf("word is %s\n", word);
			if (!(temp = ft_lstnew(word)))
				return (0);
			ft_lstadd_back(&list, temp);
			word_start = -1;
		}
		else if (**input == '|' && state != e_backslash)
		{
			if (state == e_general)
			{
				update_state(&state, &p_state, e_in_or);
				if (word_start != -1)
				{
					if (!(word = ft_strndup(*input - counter + word_start, counter - word_start)))
						return (0);
					if (!(temp = ft_lstnew(word)))
						return (0);
					ft_lstadd_back(&list, temp);
					word_start = -1;
				}
			}
			else if (state == e_in_or)
			{
				if (!(word = ft_strdup("||")))
					return (0);
				if (!(temp = ft_lstnew(word)))
					return (0);
				ft_lstadd_back(&list, temp);
				update_state(&state, &p_state, e_general);
				word_start = -1;
			}
		}
		else if (state == e_in_or && **input != '|')
		{
			//printf("pipe\n");
			if (!(word = ft_strdup("|")))
					return (0);
			if (!(temp = ft_lstnew(word)))
				return (0);
			ft_lstadd_back(&list, temp);
			update_state(&state, &p_state, e_general);
			word_start = -1;
			continue ;
		}
		else if (state == e_general && word_start == -1 && !is_white_space(**input))
		{
			word_start = counter;
		}
		else if (state == e_backslash && **input != '\\')
			update_state(&state, &p_state, p_state);
		printf("state is `%d`\n", state);
		counter++;
		(*input)++;
	}
	if ( /*state == e_general &&*/ word_start != -1)
	{
		if (!(word = ft_strndup(*input - counter + word_start, counter - word_start)))
			return (0);
		if (!(temp = ft_lstnew(word)))
			return (0);
		ft_lstadd_back(&list, temp);
	}

	return (list);
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