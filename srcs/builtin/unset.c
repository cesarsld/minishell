/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:53:07 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 18:18:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(t_list **env_list, char *key)
{
	t_var	*entry;
	t_list	*first;
	t_list	*previous;

	previous = 0;
	first = *env_list;
	while (first)
	{
		entry = first->content;
		if (ft_strcmp(key, entry->name) == 0)
		{
			free(entry->name);
			free(entry->value);
			free(entry);
			if (!previous)
				*env_list = first->next;
			else
				previous->next = first->next;
			free(first);
		}
		previous = first;
		first = first->next;
	}
}

void	remove_var_null(t_list **exp_list, char *key)
{
	t_var	*entry;
	t_list	*first;
	t_list	*previous;

	previous = 0;
	first = *exp_list;
	while (first)
	{
		entry = first->content;
		if (ft_strcmp(key, entry->name) == 0)
		{
			free(entry->name);
			free(entry->value);
			free(entry);
			if (!previous)
				*exp_list = first->next;
			else
				previous->next = first->next;
			free(first);
		}
		previous = first;
		first = first->next;
	}
}

void check_vars(t_lexer *lex, t_node *node, pid_t pid, int ret)
{
	char *word;

	if (node->left)
	{
		if (treat_word(lex, node) == FAILURE)
			return ;
		word = node->left->content;
		if ((ft_isalpha(*word) || *word == '_') &&
			is_valid_assign_n(word,ft_strlen(word)))
		{
			remove_var(&(lex->env_list), word);
			remove_var_null(&(lex->exp_list), word);
		}
		else
		{
			if (pid)
				ft_printf_err("minishell: unset: %s: not a valid identifier\n",
				word);
			ret = FAILURE;
		}
		if (node->left->left)
			return (check_vars(lex, node->left, pid, ret));
	}

}
void	unset_exec(t_lexer *lex, t_node *node)
{	
	pid_t	pid;
	int		a;

	if((pid = fork()) == 0)
		if (node->right)
			handle_redir(lex, node->right);
	check_vars(lex, node, pid, 0);
	if (!pid)
		exit(EXIT_SUCCESS);
	else
		waitpid(pid, &a, 0);
	if (WIFEXITED(a))
			*lst_rtn()  = WEXITSTATUS(a);
}