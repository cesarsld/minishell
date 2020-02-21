/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/19 13:11:45 by cjaimes          ###   ########.fr       */
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

char	*get_first_word(char *input)
{
	int count;
	char *first;
	char *word;

	count = 0;
	first = input;
	while (*input)
	{
		if (is_white_space(*input++))
			break ;
		count++;
	}
	if (!(word = ft_strndup(first, count)))
				return (0);
	return (word);
}
//TODO delete this? leaks + unused elsewhere
void wrong_command(char **input)
{
	get_first_word(*input);
}

void handle_command(char **input, t_list *env_list)
{
	char *output;
	char *command;

	output = 0;
	if (!(command = get_first_word(*input)))
		return ;
	if (ft_strlen(command) == 0)
		return ;
	if (ft_strcmp(command, "pwd") == 0)
	{
		if ((!is_white_space(*((*input) + 3)) && *((*input) + 3)))
			return (command_error(command));
		if (contains_char((*input) + 3))
			pwd_error();
		else
			output = get_pwd();
		print_ouput(output);
		// eventually add pipes here
		free(command);
		free(output);
	}
	else if (ft_strcmp(command, "cd") == 0)
	{
		if (!is_white_space(*((*input) + 2)) && *((*input) + 2))
			return (command_error(command));
		*input += 2;
		skip_whitespace(input);
		if (count_words(*input) > 1)
			cd_pwd_error(*input);
		else
		{
			// -L is by default
			// -P must be specified
			if (ft_strlen(*input) == 0 ?
				get_cd("~", env_list) == -1 : get_cd(*input, env_list) == -1)
			{
				cd_dir_error(strerror(errno), *input);
				errno = 0;
			}
			update_pwd(env_list);
		}
		// eventually add pipes here
		free(output);
		free(command);
	}
	else if (ft_strcmp(command, "env") == 0)
	{
		*input += 3;
		skip_whitespace(input);
		if (**input)
			env_error();
		else
			print_env_vars(env_list);
	}
	else if (ft_strcmp(command, "export") == 0)
	{
		*input += 6;
		skip_whitespace(input);
	}
	else
		command_error(command); 
}

t_var *new_env(char *name, char *value, int is_env)
{
	t_var *var;

	if (!(var = malloc(sizeof(t_var))))
		return (0);
	var->is_env = is_env;
	var->name = name;
	var->value = value;
	return (var);
}

t_list *get_env_vars(char **env)
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

int main(int ac, char **av, char **envac)
{
	char *user_input;
	char *copy;
	t_list *env_list;

	ac = 0;
	av = 0;

	if(!(env_list = get_env_vars(envac)))
		return (0);

	user_input = 0;
	//printf("word: |%s|\n", get_next_word("test'so'mm\"hhhhhhiiii\"h\\    this is the first line"));
	//lex_parse_line("test'so'mm\"hhhhhhiiii\"h\\    this is the first line");
	char *test = ft_strdup("'e'\"c\"\"\"'ho'\" boo\" \"   koki");
	lex_parse_line(&test);
	copy = 0;
	// while (1)
	// {
	// 	ft_putstr("> ");
	// 	if (!get_next_line(0, &user_input))
	// 		return (0);
	// 	copy = user_input;
	// 	skip_whitespace(&user_input);
	// 	handle_command(&user_input, env_list);
	// 	free (copy);

	// }
	return (0);
}
