/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:53:07 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/08 00:24:00 by cjaimes          ###   ########.fr       */
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
//this function needs to be reworked to remove the recursion since fork is happeing
void	unset_exec(t_lexer *lex, t_node *node)
{
	char *word;
	
	if (node->right)
		handle_redir(lex, node->right);
	if (node->left)
	{
		if (treat_word(lex, node) == FAILURE)
			return ;
		word = node->left->content;
		if ((ft_isalpha(*word) || *word == '_') &&
			is_valid_assign_n(word,ft_strlen(word)))
			remove_var(&(lex->env_list), word);
		else
			ft_printf_err("minishell: unset: %s: not a valid identifier\n",
				word);
		if (node->left->left)
			return (unset_exec(lex, node->left));
	}
}