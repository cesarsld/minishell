/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:25:03 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/28 23:27:45 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_bzero(g_buf, BUFFER_SIZE + 1);
		ft_bzero(g_user_input, ft_strlen(g_user_input));
		*lst_rtn() = 130;
		if (*is_in_cmd())
			ft_putstr("\n");
		else
			ft_putstr("\n(｡◕‿◕｡✿) ");
	}
	else if (signal == SIGQUIT)
	{
		if (*is_in_cmd())
		{
			*lst_rtn() = 131;
			ft_putstr("Quit: (core dumped)\n");
		}
	}
}

void	init_lexer_functions(t_lexer *lex)
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

void	init_lexer(t_lexer *lex, char *input, t_list *env_list)
{
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, &handle_signals);
	init_lexer_functions(lex);
	lex->tokens = 0;
	lex->token_start = 0;
	lex->token_len = 0;
	lex->input = input;
	lex->state = e_general;
	lex->prev_state = lex->state;
	lex->tree = 0;
	lex->p_token = e_t_word;
	lex->envac = 0;
	lex->env_list = env_list;
	lex->exp_list = 0;
	lex->w_start = 0;
	lex->len = 0;
}

void	chuck_tree(t_node *tree)
{
	if (tree)
	{
		chuck_tree(tree->right);
		chuck_tree(tree->left);
		free(tree);
	}
}

void	reset_lexer(t_lexer *lex, char *input)
{
	lex->token_start = 0;
	lex->token_len = 0;
	ft_lstclear(&(lex->tokens), &free);
	lex->input = input;
	lex->state = e_general;
	lex->prev_state = lex->state;
	chuck_tree(lex->tree);
	lex->tree = 0;
	lex->p_token = e_t_word;
}
