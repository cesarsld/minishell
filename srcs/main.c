/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/01 15:00:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int starts_with(const char *input, const char *match)
{
	return (ft_strncmp(input, match, ft_strlen(match)) == 0);  
}

int count_words(const char *input)
{
	int count;

	count = 0;
	while (*input)
	{
		if (!is_white_space(*input))
		{
			count++;
			while (*input && !is_white_space(*input))
				input++;
		}
		if (*input)
			input++;
	}
	return (count);
}

void command_error(char* err)
{
	ft_putstr("minishell: command not found: ");
	ft_putstr(err);
	ft_putstr("\n");
	return ;
}

int contains_char(const char *input)
{
	while (*input)
		if (!is_white_space(*input++))
			return (1);
	return (0);
}

void get_first_word(char *input)
{
	while (*input)
		if (is_white_space(*input))
		{
			*input = 0;
			return ;
		}
	return ;
}

void wrong_command(char **input)
{
	get_first_word(*input);
}

void handle_command(char **input)
{
	char *output;

	output = 0;
	if (starts_with(*input, "pwd ") || starts_with(*input, "pwd") )
	{
		if (contains_char((*input) + 4))
			pwd_error();
		else
			output = get_pwd();
		print_ouput(output);
		// eventually add pipes here
		free(output);
	}
	else if (starts_with(*input, "cd ") || starts_with(*input, "cd") )
	{
		*input += 2;
		skip_whitespace(input);
		if (count_words(*input) > 1)
			cd_pwd_error(*input);
		else
		{
			// -L is by default
			// -P must be specified
			if (ft_strlen(*input) == 0 ? get_cd("/~") == -1 : get_cd(*input) == -1)
			{
				cd_dir_error(strerror(errno), *input);
				errno = 0;
			}
		}
		


		//if (get_cd())
		// eventually add pipes here
		free(output);
	}
	else
		command_error(*input); 
}

int main(int ac, char **av, char **envac)
{
	char *user_input;
	char *copy;

	ac = 0;
	av = 0;
	while (*envac)
	{
		printf("env: %s\n", *envac++);
		
	}
	user_input = 0;
	while (1)
	{
		ft_putstr("> ");
		if (!get_next_line(0, &user_input))
			return (0);
		copy = user_input;
		skip_whitespace(&user_input);
		handle_command(&user_input);
		free (copy);

	}
}