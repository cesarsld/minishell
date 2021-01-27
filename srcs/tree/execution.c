/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:24:09 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 23:58:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_equal(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = malloc((len + 2) * sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len + 2);
	ft_strlcat(new, "=", len + 2);
	ft_strlcat(new, s2, len + 2);
	return (new);
}

char	**get_env_list(t_lexer *lex)
{
	char **new_list;
	t_list *first;
	int counter;
	t_var *var;

	if(!(new_list = malloc(sizeof(char*) * (ft_lstsize(lex->env_list) + 1))))
		return (NULL);
	new_list[ft_lstsize(lex->env_list)] = 0;
	first = lex->env_list;
	counter = 0;
	while (first)
	{
		var = first->content;
		if(!(new_list[counter++] = ft_strjoin_equal(var->name, var->value)))
			return (NULL);
		first = first->next;
	}
	if (lex->envac)
		free_split(lex->envac);
	lex->envac = new_list;
	return (new_list);
}

int		is_dir(char *name)
{
	if(opendir(name))
	{
		ft_printf_err("minishell: %s: %s\n", name, "is a directory");
		exit(1);
	}
	return (0);
}

int		is_builtin(t_lexer *lex, t_node *node)
{
	if (!node->content || treat_word(lex, node) == FAILURE)
		return (FAILURE);
	else if (ft_strcmp("cd", node->content) == 0)
		cd_exec(lex, node);
	else if (ft_strcmp("export", node->content) == 0)
		export_exec(lex, node);
	else if (ft_strcmp("unset", node->content) == 0)
		unset_exec(lex, node);
	else if (ft_strcmp("pwd", node->content) == 0)
	 	pwd_exec(lex, node);
	else if (ft_strcmp("env", node->content) == 0)
		env_exec(lex, node);
	else if (ft_strcmp("echo", node->content) == 0)
		echo_exec(lex, node);
	else if (ft_strcmp("exit", node->content) == 0)
		exit_exec(lex, node);
	else
		return (FAILURE);
	return (SUCCESS);
}

void	execute_tree(t_lexer *lex, t_node *node)
{
	if (!node)
		return ;
	if (node->type == e_t_semi_colon)
	{
		execute_tree(lex, node->left);
		execute_tree(lex, node->right);
	}
	else if (node->type == e_t_cmd_name)
		is_builtin(lex, node) == SUCCESS ? 0 : handle_cmd_exec(lex, node);
	else if (node->type == e_t_pipe)
		return (execute_pipe(node, lex, STDOUT_FILENO));
}
