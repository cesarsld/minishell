/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:26:58 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 01:56:25 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_lexer *lex, t_node *node)
{
	if (!node->content || treat_word(lex, node) == FAILURE)
		return ;
	ft_putstr(node->content);
	if (node->left)
	{
		ft_putstr(" ");
		print_args(lex, node->left);
	}
}

void	echo_exec(t_lexer *lex, t_node *node)
{
	int		is_opt;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		is_opt = 0;
		node->right ? handle_redir(lex, node->right) : 0;
		if (!node->left)
		{
			ft_printf("\n");
			exit(EXIT_SUCCESS);
		}
		is_opt = ft_strcmp(node->left->content, "-n") == 0 ? 1 : 0;
		while (ft_strcmp(node->left->content, "-n") == 0)
			node = node->left;
		print_args(lex, node->left);
		if (!is_opt)
			ft_putstr("\n");
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &is_opt, 0);
	*lst_rtn() = WIFEXITED(is_opt) ? WEXITSTATUS(is_opt) : *lst_rtn();
}
