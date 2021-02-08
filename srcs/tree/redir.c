/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:50:20 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/08 17:01:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_last_redir(t_node *node, enum e_token_type type,
	enum e_token_type type2)
{
	t_node *cur;

	cur = node;
	while (cur)
	{
		if (cur->type == type || cur->type == type2)
			return (0);
		cur = cur->left;
	}
	return (1);
}

void	handle_d_supp_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		perror("open()");
		exit(FAILURE);
	}
	if (node->left)
	{
		if (check_if_last_redir(node->left, e_t_d_supp, e_t_supp))
		{
			dup2(fd, STDOUT_FILENO);
		}
		handle_redir(lex, node->left);
		close(fd);
	}
	else
		dup2(fd, STDOUT_FILENO);
}

void	handle_supp_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		perror("open()");
		exit(FAILURE);
	}
	if (node->left)
	{
		if (check_if_last_redir(node->left, e_t_d_supp, e_t_supp))
		{
			dup2(fd, STDOUT_FILENO);
		}
		handle_redir(lex, node->left);
		close(fd);
	}
	else
		dup2(fd, STDOUT_FILENO);
}

void	handle_inf_redir(t_lexer *lex, t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_RDONLY)) == -1)
	{
		ft_printf("minishell: %s: %s\n", strerror(errno), node->content);
		exit(errno);
	}
	if (node->left)
	{
		if (check_if_last_redir(node->left, e_t_inf, e_t_inf))
		{
			dup2(fd, STDIN_FILENO);
		}
		handle_redir(lex, node->left);
		close(fd);
	}
	else
		dup2(fd, STDIN_FILENO);
}

void	handle_redir(t_lexer *lex, t_node *node)
{
	if (treat_word(lex, node) == FAILURE)
		exit(1);
	if (node->type == e_t_supp)
		handle_supp_redir(lex, node);
	else if (node->type == e_t_inf)
		handle_inf_redir(lex, node);
	else if (node->type == e_t_d_supp)
		handle_d_supp_redir(lex, node);
}
