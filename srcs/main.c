/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:26:48 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*is_in_cmd(void)
{
	static int i = 0;

	return (&i);
}

int		*lst_rtn(void)
{
	static int ret = 0;

	return (&ret);
}

int		fetch_input_words(t_lexer *lex)
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
			lex->state == e_s_quote ? "single" : "double");
		return (1);
	}
	return (0);
}

void	reset_loop(char **user_input)
{
	free(*user_input);
	*user_input = 0;
	ft_putstr("(｡◕‿◕｡✿) ");
	*is_in_cmd() = 0;
	if (!get_next_line(STDIN_FILENO, user_input))
	{
		ft_printf("exit\n");
		exit(0);
	}
}

int		main(int ac, char **av, char **envac)
{
	char	*user_input;
	t_lexer	lex;
	t_list	*env_list;

	if (ac || av)
	{
	}
	if (!(env_list = get_env_vars(envac)))
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
