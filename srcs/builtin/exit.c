/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:18:20 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/01 13:07:17 by cjaimes          ###   ########.fr       */
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
			exit(255);
		}
	}
	ft_printf("exit\n");
	exit(*lst_rtn());
}
