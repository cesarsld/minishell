/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:32:16 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/20 17:50:56 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>

typedef enum			e_token_type
{
	e_command = 0, e_option = 1, e_input = 2, e_prog = 3
}						t_oken_type;

# define LEX_STATES 10

typedef enum			e_lex_state
{
	e_general = 0, e_s_quote = 1, e_d_quote = 2, e_backslash = 3, e_in_and = 4,
	e_in_or = 5, e_in_semi_colon = 6, e_in_redir_supp = 7, e_in_redir_inf = 8,
	e_error = 9
}						t_lex_state;
/*
** These functions switch the lexer states depending on input
** typedef void			(*t_lex_transition)(char, t_lexer *);
*/
typedef int				(*t_lex_action)(char, t_list **);

typedef struct			s_lexer
{
	t_lex_state			prev_state;
	t_lex_state			state;
	t_lex_action		actions[LEX_STATES];
	void				(*transitions[LEX_STATES])(char, struct s_lexer *);
}						t_lexer;

typedef struct			s_env_var
{
	char				*name;
	char				*value;
	int					is_env;
}						t_var;

typedef struct			s_char
{
	char*				value;
}						t_char;

char					*get_next_word(char **input, char *q_type);
t_list					*lex_parse_line(char **line);
t_list					*lex_it(char **input);
int						lex_it_(t_list **alst, char *input, t_lexer *lex);

int						is_white_space(char c);
void					skip_whitespace(char **line);
int						print_ouput(char *out);
int						starts_with(const char *input, const char *match);

t_var					*new_env(char *name, char *value, int is_env);

void					pwd_error();
char					*get_pwd();
int						update_pwd(t_list *env_list);

int						get_cd(const char *dir, t_list *env_list);
void					cd_error(const char *dir);
void					cd_pwd_error(char *dir);
void					cd_dir_error(char *err, const char *dir);

void					print_env_vars(t_list *env_list);
void					env_error();
t_var					*get_var(t_list *env_list, char *key);

/*
** Transitions and actions
*/
void					from_general(char c, t_lexer *lex);
void					from_s_quote(char c, t_lexer *lex);
void					from_d_quote(char c, t_lexer *lex);
void					from_backslash(char c, t_lexer *lex);
void					from_in_and(char c, t_lexer *lex);
void					from_in_or(char c, t_lexer *lex);
void					from_in_semi_colon(char c, t_lexer *lex);
void					from_in_redir_supp(char c, t_lexer *lex);
void					from_in_redir_inf(char c, t_lexer *lex);
void					from_error(char c, t_lexer *lex);

#endif
