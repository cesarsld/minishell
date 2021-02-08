/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:32:14 by cjaimes           #+#    #+#             */
/*   Updated: 2021/02/08 14:08:54 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cwd_err(void)
{
	ft_printf_err("minishell: cd: error retrieving current directory:");
	ft_printf_err(" getcwd: cannot access parent directories");
	ft_printf_err(": No such file or directory\n");
}

int		create_pwd_var_if_null(t_lexer *lex, char const *var, char *pwd)
{
	char *temp;

	temp = ft_strjoin(var, pwd);
	if (add_var(lex, temp))
	{
		free(temp);
		return FAILURE;
	}
	free(temp);
	return (SUCCESS);
}

int		handle_pwd(t_lexer *lex, t_var *pwd_var, char *temp, char **plc_var)
{
	if (!pwd_var)
	{
		if (create_pwd_var_if_null(lex, "PWD=", temp))
			return (1);
	}
	else
	{
		*plc_var = pwd_var->value;
		if (!(pwd_var->value = ft_strdup(temp)))
			return (1);
	}
	return (0);
}

int		handle_old_pwd(
	t_lexer *lex, t_var *old_pwd_var, char *plc_var)
{
	if (!old_pwd_var)
	{
		if (create_pwd_var_if_null(lex, "OLDPWD=", plc_var))
			return (1);
		plc_var ? free(plc_var) : 0;
	}
	else
	{
		free(old_pwd_var->value);
		old_pwd_var->value = plc_var;
	}
	return (0);
}

int		update_pwd(t_lexer *lex, char *path, pid_t pid)
{
	t_var	*pwd_var;
	t_var	*old_pwd_var;
	char	*temp;
	char	*plc;
	char	*plc_var;

	plc_var = 0;
	temp = get_pwd();
	plc = lex->pwd;
	pwd_var = get_var(lex->env_list, "PWD");
	old_pwd_var = get_var(lex->env_list, "OLDPWD");
	if (!temp)
	{
		if (pid == 0)
			print_cwd_err();
		temp = ft_strpathjoin(lex->pwd, path);
	}
	if (handle_pwd(lex, pwd_var, temp, &plc_var))
		return (1);
	lex->pwd = temp;
	if (handle_old_pwd(lex, old_pwd_var, plc_var))
		return (1);
	free(lex->oldpwd);
	lex->oldpwd = plc;
	return (0);
}
