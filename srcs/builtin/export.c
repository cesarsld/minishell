/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:04:32 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/08 11:06:46 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int contains_char(const char *input, char chr)
{
	while (*input)
		if (*input++ == chr)
			return (1);
	return (0);
}

int is_valid_assign_n(char *word, int len)
{
	while (len--)
		if (!is_name_char(*word++))
			return (0);
	return (1);
}


int add_var(t_list *env_list, char *input)
{
	t_var   *new;
	t_list	*temp;
	t_var	*exist;
	char	*name;
	char	*value;

	if (!(name = ft_strndup(input, ft_strchr(input, '=') - input)))
			return (FAILURE);
	if (!(value = ft_strdup(ft_strchr(input, '=') + 1)))
			return (FAILURE);
	if ((exist = get_var(env_list, name)))
	{
		free(exist->value);
		exist->value = value;
		free(name);
		return (SUCCESS);
	}
	if (!(new = new_env(name, value, 1)))
		return (FAILURE);
	if (!(temp = ft_lstnew(new)))
		return (FAILURE);
	ft_lstadd_back(&env_list, temp);
	return (SUCCESS);
}

void check_exports(t_lexer *lex, t_node *node, pid_t pid)
{
	char	*word;

	if (node->left)
	{
		if (treat_word(lex, node->left) == FAILURE)
			return ;
		word = node->left->content;
		if ((ft_isalpha(*word) || *word == '_') &&
			is_valid_assign_n(word, ft_strchr(word, '=')?
			ft_strchr(word, '=') - word : ft_strlen(word)))
		{
			if (contains_char(word, '='))
				if (add_var(lex->env_list, word) == FAILURE)
					exit(EXIT_FAILURE);
		}
		else
		{
			if (!pid)
				ft_printf_err("minishell: export: %s: not valid identifier\n",
				word);
		}
		if (node->left->left)
			return (check_exports(lex, node->left, pid));
	}
}

void	export_exec(t_lexer *lex, t_node *node)
{
	pid_t	pid;
	int		a;
	
	if((pid = fork()) == 0)
		if (node->right)
			handle_redir(lex, node->right);
	check_exports(lex, node, pid);
	if (!node->left && !pid)
	{
		print_env_vars(lex->env_list);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &a, 0);
}
