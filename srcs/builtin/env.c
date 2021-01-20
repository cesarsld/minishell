/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:55:04 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/20 17:15:42 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env_var(void *content)
{
	t_var *var;

	var = content;
	if (var->is_env)
	{
		ft_putstr(var->name);
		ft_putstr("=");
		ft_putstr(var->value);
		ft_putstr("\n");
	}
}

void print_export_var(void *content)
{
	t_var *var;

	var = content;
	if (var->is_env)
	{
		ft_putstr("declare -x ");
		ft_putstr(var->name);
		ft_putstr("=");
		ft_putstr("\"");
		ft_putstr(var->value);
		ft_putstr("\"");
		ft_putstr("\n");
	}
}

void print_export_var_null(void *content)
{
	t_var *var;

	var = content;
	if (var->is_env)
	{
		ft_putstr("declare -x ");
		ft_putstr(var->name);
		ft_putstr("\n");
	}
}

t_var	*get_var(t_list *env_list, char *key)
{
	t_var *entry;
	
	while (env_list)
	{
		entry = env_list->content;
		if (ft_strcmp(key, entry->name) == 0)
			return (entry);
		env_list = env_list->next;
	}
	return (0);
}

char	*get_var_value(t_list *env_list, char *key)
{
	t_var	*entry;
	
	while (env_list)
	{
		entry = env_list->content;
		if (ft_strcmp(key, entry->name) == 0)
			return (entry->value);
		env_list = env_list->next;
	}
	return (0);
}

void    print_env_vars(t_lexer *lex, int env)
{
	if (env)
		ft_lstiter(lex->env_list, &print_env_var);
	else
	{
		ft_lstiter(lex->env_list, &print_export_var);
		ft_lstiter(lex->exp_list, &print_export_var_null);
	}
}

void env_exec(t_lexer *lex, t_node *node)
{
	pid_t	pid;
	int		a;
	
	if((pid = fork()) == 0)
	{
		if(node->right)
			handle_redir(lex, node->right);
		if (node->left)
		{
			ft_printf_err("bash: env: too many arguments or options\n");
			return ;
		}
		print_env_vars(lex, 1);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &a, 0);
	
}
