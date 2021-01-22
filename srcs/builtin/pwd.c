/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:18:17 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/22 15:54:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char *path_name;

	path_name = NULL;
	path_name = getcwd(path_name, 0);
	return (path_name);
}

char	*ft_strpathjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(new = malloc((len + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len + 1);
	if (*(s1 + ft_strlen(s1) - 1) == '/')
		*(new + ft_strlen(s1) - 1) = 0;
	ft_strlcat(new, "/", len + 1);
	ft_strlcat(new, s2, len + 1);
	return (new);
}

int		update_pwd(t_list *env_list, char* path)
{
	t_var *pwd_var;
	t_var *old_pwd_var;
	char *temp;

	temp = get_pwd();
	if (!(pwd_var = get_var(env_list, "PWD")))
		return (0);
	if (!temp)
	{
		temp = ft_strpathjoin(pwd_var->value, path);
		ft_printf_err("minishell: cd: error retrieving current directory:");
		ft_printf_err(" getcwd: cannot access parent directores");
		ft_printf_err(": No such file or directory\n");	
	}
	if ((old_pwd_var = get_var(env_list, "OLDPWD")))
	{
		free(old_pwd_var->value);
		old_pwd_var->value = pwd_var->value;
	}
	else
		free(pwd_var->value);
	if(!(pwd_var->value = ft_strdup(temp)))
		return (0);
	free(temp);
	return (1);
}

void pwd_exec(t_lexer *lex, t_node *node)
{
	pid_t	pid;
	int		a;

	if((pid = fork()) == 0)
	{
		if(node->right)
			handle_redir(lex, node->right);
		if (node->left)
		{
			ft_printf_err("bash: pwd: too many arguments or options\n");
			exit(EXIT_SUCCESS);
		}
		ft_printf("%s\n", get_var(lex->env_list, "PWD")->value);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &a, 0);
}