/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:32:16 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/18 17:42:53 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <string.h>
#include <stdio.h>

typedef enum		e_token_type
{
	e_command = 0, e_option = 1, e_input = 2, e_prog = 3
}					t_oken_type;

typedef struct	s_env_var
{
	char		*name;
	char		*value;
	int			is_env;
}				t_var;

typedef struct	s_token
{
	char*		value;
	int			type;
	int			literal;
}				t_oken;


char	*get_next_word(char *input, char *q_type);
t_list *lex_parse_line(char *line);

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