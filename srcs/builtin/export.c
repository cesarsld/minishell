/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:04:32 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/27 02:30:37 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_var(t_lexer *lex, char *input)
{
	t_var	*new;
	t_list	*temp;
	t_var	*exist;
	char	*name;
	char	*value;

	if (!(name = ft_strndup(input, ft_strchr(input, '=') - input)))
		return (FAILURE);
	if (!(value = ft_strdup(ft_strchr(input, '=') + 1)))
		return (FAILURE);
	if ((exist = get_var(lex->env_list, name)))
	{
		free(exist->value);
		exist->value = value;
		free(name);
		return (SUCCESS);
	}
	if (get_var(lex->exp_list, name))
		remove_var_null(&(lex->exp_list), name);
	if (!(new = new_env(name, value, 1)))
		return (FAILURE);
	if (!(temp = ft_lstnew(new)))
		return (FAILURE);
	ft_lstadd_back(&(lex->env_list), temp);
	return (SUCCESS);
}

int		add_var_null(t_lexer *lex, char *input)
{
	t_var	*new;
	t_list	*temp;
	char	*name;

	if (!(name = ft_strdup(input)))
		return (FAILURE);
	if (get_var(lex->env_list, name) || get_var(lex->exp_list, name))
	{
		free(name);
		return (SUCCESS);
	}
	if (!(new = new_env(name, 0, 1)))
		return (FAILURE);
	if (!(temp = ft_lstnew(new)))
		return (FAILURE);
	ft_lstadd_back(&(lex->exp_list), temp);
	return (SUCCESS);
}

void	check_exports(t_lexer *lex, t_node *node, pid_t pid, int ret)
{
	char	*word;

	if (node->left)
	{
		if (treat_word(lex, node->left) == FAILURE)
			return ;
		word = node->left->content;
		if ((ft_isalpha(*word) || *word == '_') &&
			is_valid_assign_n(word, ft_strchr(word, '=') ?
				ft_strchr(word, '=') - word : ft_strlen(word)))
		{
			if ((contains_char(word, '=') && add_var(lex, word) == FAILURE) ||
				add_var_null(lex, word) == FAILURE)
				exit(EXIT_FAILURE);
		}
		else if (!pid)
		{
			ft_printf_err("minishell: export: %s: not valid identifier\n",
			word);
			ret = FAILURE;
		}
		if (node->left->left)
			return (check_exports(lex, node->left, pid, ret));
		pid == 0 ? exit(ret) : 0;
	}
}

void	export_exec(t_lexer *lex, t_node *node)
{
	pid_t	pid;
	int		a;

	if ((pid = fork()) == 0)
		if (node->right)
			handle_redir(lex, node->right);
	check_exports(lex, node, pid, 0);
	if (!pid)
	{
		if (!node->left)
			print_env_vars(lex, 0);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &a, 0);
	if (WIFEXITED(a))
		*lst_rtn() = WEXITSTATUS(a);
}
