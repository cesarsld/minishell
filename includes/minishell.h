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

# define LEX_STATES 11

typedef enum			e_lex_state
{
	e_general,
	e_word,
	e_s_quote,
	e_d_quote,
	e_backslash,
	e_and,
	e_or,
	e_semi_colon,
	e_supp,
	e_inf,
	e_error
}						t_lex_state;

/*
** These functions switch the lexer states depending on input
** typedef void			(*t_lex_transition)(char, t_lexer *);
** typedef int				(*t_lex_action)(char, t_list **);
*/

typedef struct			s_lexer
{
	t_lex_state			prev_state;
	t_lex_state			state;
	int					(*actions[LEX_STATES])(struct s_lexer *);
	void				(*transitions[LEX_STATES])(char, struct s_lexer *);
	t_list				*tokens;
	char				*input;
	size_t				token_start;
	size_t				token_len;
}						t_lexer;

typedef struct			s_env_var
{
	char				*name;
	char				*value;
	int					is_env;
}						t_var;

char					*get_next_word(char **input, char *q_type);
t_list					*lex_parse_line(char **line);
t_list					*lex_it(char **input);
int						lex_it_(t_lexer *lex);

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
void					from_word(char c, t_lexer *lex);
void					from_s_quote(char c, t_lexer *lex);
void					from_d_quote(char c, t_lexer *lex);
void					from_backslash(char c, t_lexer *lex);
void					from_and(char c, t_lexer *lex);
void					from_or(char c, t_lexer *lex);
void					from_semi_colon(char c, t_lexer *lex);
void					from_supp(char c, t_lexer *lex);
void					from_inf(char c, t_lexer *lex);
void					from_error(char c, t_lexer *lex);

int						act_general(t_lexer *lex);
int						act_word(t_lexer *lex);
int						act_s_quote(t_lexer *lex);
int						act_d_quote(t_lexer *lex);
int						act_backslash(t_lexer *lex);
int						act_and(t_lexer *lex);
int						act_or(t_lexer *lex);
int						act_semi_colon(t_lexer *lex);
int						act_supp(t_lexer *lex);
int						act_inf(t_lexer *lex);
int						act_error(t_lexer *lex);

#endif
