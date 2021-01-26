/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 22:37:59 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*is_in_cmd(void)
{
	static int i = 0;

	return (&i);
}

int *lst_rtn(void)
{
	static int ret = 0;

	return (&ret);
}

int fetch_input_words(t_lexer *lex)
{
	size_t input_len;

	input_len = (size_t)ft_strlen(lex->input);
	while (lex->token_start + lex->token_len <= input_len)
	{
		if (lex->actions[lex->state](lex))
			return (1);
		lex->transitions[lex->state](lex);
	}
	if (lex->token_len)
		push_token(lex);
	if (lex->state == e_s_quote || lex->state == e_d_quote)
	{
		ft_printf_err("minishell: syntax error: missing %s quote end\n",
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
	case e_t_inf:
		return ("INF");
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
				node->content? "->":"", node->content ? (char*)node->content:"");
	if (node->left)
		print_tree(node->left, level + 1, 0);
	if (node->right)
		print_tree(node->right, level + 1, 1);
}

void reset_loop(char **user_input)
{
	free(*user_input);
	*user_input = 0;
	// ft_putstr("(｡◕‿◕｡✿) ");
	*is_in_cmd() = 0;
	if (!get_next_line(STDIN_FILENO, user_input))
	{
		// ft_printf("exit\n");
		exit(0);
	}
}

int main(int ac, char **av, char **envac)
{
	char *user_input;
	t_lexer lex;
	t_list *env_list;

	if (ac || av)
	{
	}
	if(!(env_list = get_env_vars(envac)))
		return (0);
	user_input = 0;
	init_lexer(&lex, 0, env_list);
	while (1)
	{
		reset_loop(&user_input);
		*is_in_cmd() = 1;
		reset_lexer(&lex, user_input);
		if (fetch_input_words(&lex))
			continue;
		if (generate_tree(&lex))
			continue;
		execute_tree(&lex, lex.tree);
	}
	return (0);
}
