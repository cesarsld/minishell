/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 14:03:45 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/errno.h>

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

pid_t get_set_pid(int opt, pid_t value)
{
	static pid_t id = 0;

	if (opt == 0)
		return id;
	else if (opt == 1)
	{
		id = value;
		return (0);
	}
	else if (opt == 2)
	{
		id = 0;
		return (0);
	}
	return (0);
}

void kill_current_process(int signal)
{
	pid_t pid;

	printf("Killing process... signal %d\n", signal);
	if ((pid = get_set_pid(0, 0)) != 0)
		kill(pid, signal);
		
	// if (id == 0)
	// {
	// 	kill(id, signal);
	// }
}

void print_words(void *content)
{
	printf("Word: `%s`\n", (char *)content);
}

void init_lexer_functions(t_lexer *lex)
{
	lex->actions[e_general] = &act_general;
	lex->actions[e_word] = &act_word;
	lex->actions[e_s_quote] = &act_s_quote;
	lex->actions[e_d_quote] = &act_d_quote;
	lex->actions[e_backslash] = &act_backslash;
	lex->actions[e_and] = &act_and;
	lex->actions[e_or] = &act_or;
	lex->actions[e_semi_colon] = &act_semi_colon;
	lex->actions[e_supp] = &act_supp;
	lex->actions[e_inf] = &act_inf;
	lex->actions[e_error] = &act_error;
	lex->transitions[e_general] = &from_general;
	lex->transitions[e_word] = &from_word;
	lex->transitions[e_s_quote] = &from_s_quote;
	lex->transitions[e_d_quote] = &from_d_quote;
	lex->transitions[e_backslash] = &from_backslash;
	lex->transitions[e_and] = &from_and;
	lex->transitions[e_or] = &from_or;
	lex->transitions[e_semi_colon] = &from_semi_colon;
	lex->transitions[e_supp] = &from_supp;
	lex->transitions[e_inf] = &from_inf;
	lex->transitions[e_error] = &from_error;
}

void init_lexer(t_lexer *lex, char *input, char **envac, t_list *env_list)
{
	init_lexer_functions(lex);
	lex->tokens = 0;
	lex->token_start = 0;
	lex->token_len = 0;
	lex->input = input;
	lex->state = e_general;
	lex->prev_state = lex->state;
	lex->tree = 0;
	lex->previous_token = e_t_word;
	lex->envac = envac;
	lex->env_list = env_list;
}

void chuck_tree(t_node *tree)
{
	if (tree)
	{
		chuck_tree(tree->right);
		chuck_tree(tree->left);
		free(tree);
	}
}

void reset_lexer(t_lexer *lex, char *input)
{
	lex->token_start = 0;
	lex->token_len = 0;
	ft_lstclear(&(lex->tokens), &free);
	free(lex->input);
	lex->input = input;
	lex->state = e_general;
	lex->prev_state = lex->state;
	chuck_tree(lex->tree);
	lex->tree = 0;
	lex->previous_token = e_t_word;
}

int fetch_input_words(t_lexer *lex)
{
	size_t input_len;

	input_len = (size_t)ft_strlen(lex->input);
	while (lex->token_start + lex->token_len <= input_len /*&& lex->input[lex->token_start + lex->token_len]*/)
	{
		if (lex->actions[lex->state](lex))
			return (1);
		lex->transitions[lex->state](lex);
	}
	if (lex->token_len)
		push_token(lex);
	if (lex->state == e_s_quote || lex->state == e_d_quote)
	{
		ft_printf_err("minishell: syntax error missing %s quote end\n",
			lex->state == e_s_quote? "single" : "double");
		return (1);
	}
	return (0);
}

const char* get_token_type(t_oken_type type)
{
	switch (type)
	{
	case e_t_cmd_name:
		return ("CMD_NAME");
	case e_t_cmd_word:
		return ("CMD_WORD");
	case e_t_semi_colon:
		return ("SEMI_COLON");
	case e_t_pipe:
		return ("PIPE");
	case e_t_supp:
		return ("SUPP");
	default:
		return ("");
	}
}

void print_tree(t_node *node, int level, int lr)
{
	if(lr == 2)
		printf("Level %d | %-10s | token type is %s\n", level, "root",get_token_type(node->type));
	else
		printf("Level %d | %-5s side | token type is %s%s%s\n",
				level, lr? "Right" : "Left", get_token_type(node->type),
				node->content? "->":"", node->content ? node->content:"");
	if (node->left)
		print_tree(node->left, level + 1, 0);
	if (node->right)
		print_tree(node->right, level + 1, 1);
}

int main(int ac, char **av, char **envac)
{
	char *user_input;
	char *copy;
	t_list *env_list;

	ac = 0;
	av = 0;
	//while (*av)
		//printf("%s\n", *av++);

	if(!(env_list = get_env_vars(envac)))
		return (0);

	user_input = 0;
	// char *test = ft_strdup("'e'\"c\"\"\"'ho'\" boo\" \"   koki");
	//get_command_path(get_var(env_list, "PATH")->value, "cat");

	//char *test = ft_strdup("e'c'h\"l\"o boo what\\\'s  babe;;I;got;thestyle  up|||||su|is je a>r>>rive ici |le pipe |c\\\'est cool  |\"Le cheval c'est trop genial\"'senpai'|  \\t    end  ");
	//char *test = ft_strdup("echo boo haha bingo ; echo boo haha ; echo top; echo boom peck");
	//char *test = ft_strdup("echo boo haha bingo | echo boo haha | echo boo ; echo top | echo boom peck ; echo tech beck");
	//char *test = ft_strdup("33>>>boo 3> gaa >> > >>>>> echo boo 45 >boo");
	//char *test = ft_strdup(">foo >bar echo meh >tap boo | >boom echo tech ; echo bass >bee | >mambo echo tree  | echo trump >boo ");
	//char *test = ft_strdup("tech    ");
	//t_list *words = lex_it(&test);
	t_lexer lex;
	//init_lexer(&lex, test, envac);
	//fetch_input_words(&lex);
	//generate_tree(&lex);
	//t_node *tree = generate_tree(&lex);
	//printf("%p\n", tree);
	//if (lex.tree)
	//	print_tree(lex.tree, 0, 2);
	//printf("boo");


	// t_node *n = create_new_node(e_t_supp);
	// n->content = ft_strdup("hello");
	// handle_supp_redir(n);

	init_lexer(&lex, 0, envac, env_list);
	while (1)
	{
		ft_putstr("(｡◕‿◕｡✿) ");
		if (!get_next_line(0, &user_input))
		{
			ft_printf("exit\n");
			return (0);
		}
		copy = user_input;
		skip_whitespace(&user_input);
		reset_lexer(&lex, copy);
		if(fetch_input_words(&lex))
			continue;
		//ft_lstiter(lex.tokens, &print_words);
		if (generate_tree(&lex))
			continue;
		//print_tree(lex.tree, 0, 2);
		execute_tree(&lex, lex.tree);
	}



	//t_list *words = lex_it(&test);
	//printf("word: |%s|\n", get_next_word("test'so'mm\"hhhhhhiiii\"h\\    this is the first line"));
	//ft_lstiter(lex.tokens, &print_words);
	//printf("\n\n");
	//ft_lstiter(words, &print_words);
	//char *test = ft_strdup("'e'\"c\"\"\"'ho'\" boo\" \"   koki");
	//lex_parse_line(&test);
	copy = 0;


	// pid_t new_id = fork();
	// if (new_id == 0)
	// {
	// 	printf("id is %d\n", new_id);
		// char *name = strdup("echo");
		// char **arg = malloc(sizeof(char *) * 2);
		// arg[1] = 0;
		// arg[0] = name;

		// execve("echo", arg, envac);
	// 	perror("");

	// }
	// else
	// {
	// 	int a = 0;
	// 	get_set_pid(1, new_id);
	// 	signal(SIGINT, &kill_current_process);
	// 	signal(SIGQUIT, &kill_current_process);
	// 	//signal(SIG, &kill_current_process);
	// 	waitpid(new_id, &a , 0);

	// }


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
