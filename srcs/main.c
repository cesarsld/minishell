/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:12:19 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/03 18:10:58 by cjaimes          ###   ########.fr       */
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

int		reset_loop(char **user_input, int *ctrl_d, t_lexer *lex)
{
	free(*user_input);
	*user_input = 0;
	if (*ctrl_d)
	{
		*ctrl_d = 0;
		return (1);
	}
	else
		ft_putstr("(｡◕‿◕｡✿) ");
	*is_in_cmd() = 0;
	if (!get_next_line_shell(STDIN_FILENO, user_input))
	{
		ft_printf("exit\n");
		exit_clean(lex, 0);
	}
	return (0);
}

int		main(int ac, char **av, char **envac)
{
	t_lexer	lex;
	t_list	*env_list;

	(void)av;
	if (!(env_list = get_env_vars(envac)))
		return (0);
	g_user_input = 0;
	ac = 0;
	init_lexer(&lex, 0, env_list);
	while (1)
	{
		if (reset_loop(&g_user_input, &ac, &lex))
			continue;
		*is_in_cmd() = 1;
		reset_lexer(&lex, g_user_input);
		if (fetch_input_words(&lex))
			continue;
		if (generate_tree(&lex))
			continue;
		execute_tree(&lex, lex.tree);
	}
	return (0);
}
