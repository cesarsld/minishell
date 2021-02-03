/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:18:20 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/03 18:42:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_num_exit(char const *arg, t_node *node)
{
	if (node->left->left)
	{
		ft_printf_err("minishell: exit: too many arguments\n", 255);
		*lst_rtn() = 1;
		return (1);
	}
	exit(ft_atoi(arg) % 256);
}

int		is_number_n_e(char *input, int size)
{
	char	*start;
	int		neg;

	neg = 0;
	if (*input == '+' || *input == '-')
	{
		neg = *input == '-' ? 1 : 0;
		input++;
		size--;
	}
	start = input;
	while (size-- > 0)
		if (!ft_isdigit(*input++))
			return (0);
	if (!neg && ft_strcmp(start, "9223372036854775807") > 0)
		return (0);
	else if (neg && ft_strcmp(start, "9223372036854775808") > 0)
		return (0);
	return (1);
}

void	clean_env(void *env)
{
	t_var *var;

	var = env;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
}

void	exit_clean(t_lexer *lex, int ret)
{
	if (g_user_input)
		free(g_user_input);
	g_user_input = 0;
	ft_lstiter(lex->env_list, &clean_env);
	ft_lstiter(lex->exp_list, &clean_env);
	ft_lstclear(&(lex->env_list), &free);
	ft_lstclear(&(lex->exp_list), &free);
	ft_lstclear(&(lex->tokens), &free);
	chuck_tree(lex->tree);
	exit(ret);
}

void	exit_exec(t_lexer *lex, t_node *node)
{
	char *arg;

	node->right ? handle_redir(lex, node->right) : 0;
	if (node->left)
	{
		if (!node->left->content || treat_word(lex, node->left) == FAILURE)
			return ;
		arg = node->left->content;
		ft_printf_err("exit\n");
		if (is_number_n_e(arg, ft_strlen(arg)))
		{
			if (is_num_exit(arg, node))
				return ;
		}
		else
		{
			ft_printf_err("minishell: exit: %s: numeric argument required\n",
				node->left->content);
			exit_clean(lex, 255);
		}
	}
	ft_printf("exit\n");
	exit_clean(lex, *lst_rtn());
}
