/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:32:16 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/06 12:08:22 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <string.h>
#include <stdio.h>

typedef struct	s_env_var
{
	char		*name;
	char		*value;
	int			is_env;
}				t_var;

int				is_white_space(char c);
void			skip_whitespace(char **line);
int				print_ouput(char *out);
int				starts_with(const char *input, const char *match);

t_var			*new_env(char *name, char *value, int is_env);

void			pwd_error();
char			*get_pwd();
int				update_pwd(t_list *env_list);

int				get_cd(const char *dir, t_list *env_list);
void			cd_error(const char *dir);
void			cd_pwd_error(char *dir);
void			cd_dir_error(char * err, const char *dir);

void			print_env_vars(t_list *env_list);
void			env_error();
t_var			*get_var(t_list *env_list, char *key);

# endif