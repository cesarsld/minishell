/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:18:20 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/08 11:10:51 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_exec(t_lexer *lex, t_node *node)
{
	char *arg;

	if(node->right)
		handle_redir(lex, node->right);
	if (node->left)
	{
		if (!node->left->content || treat_word(lex, node->left) == FAILURE)
			return ;
		arg = node->left->content;
		ft_printf_err("exit\n");
		if (is_number_n(arg, ft_strlen(arg)))
			exit(ft_atoi(arg) > 255 ? 255 : ft_atoi(arg));
		else
		{
			ft_printf_err("bash: exit: %s: numeric argument required\n", node->left->content);
			exit(255);
		}
	}
	ft_printf_err("exit\n");
	exit(EXIT_SUCCESS);
}