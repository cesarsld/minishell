/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:18:20 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 20:14:02 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_with_err(char const *msg, int val)
{
	ft_printf_err(msg);
	exit(val);
}

void exit_exec(t_lexer *lex, t_node *node)
{
	char *arg;

	node->right ? handle_redir(lex, node->right) : 0;
	if (node->left)
	{
		if (!node->left->content || treat_word(lex, node->left) == FAILURE)
			return ;
		arg = node->left->content;
		ft_printf_err("exit\n");
		if (is_number_n(arg, ft_strlen(arg)))
		{
			if (node->left->left)
				exit_with_err("bash: exit: too many arguments\n", 255);
			exit(ft_atoi(arg) > 255 ? 255 : ft_atoi(arg));
		}
		else
		{
			ft_printf_err("bash: exit: %s: numeric argument required\n",
				node->left->content);
			exit(255);
		}
	}
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}