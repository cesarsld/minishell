/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:32:16 by cjaimes           #+#    #+#             */
/*   Updated: 2021/01/26 17:46:40 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

# define LEX_STATES 11
# define FAILURE 1
# define SUCCESS 0
# define M_ERROR -1

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

typedef enum			e_token_type
{
	e_t_word,
	e_t_cmd_word,
	e_t_cmd_name,
	e_t_assignment_word,
	e_t_pipe,
	e_t_name,
	e_t_semi_colon,
	e_t_supp,
	e_t_d_supp,
	e_t_inf,
	e_t_append,
	e_t_cd, 
	e_t_echo,
	e_t_export,
	e_t_env,
	e_t_pwd
}						t_oken_type;

typedef struct			s_node
{
	t_oken_type			type;
	struct s_node		*left;
	struct s_node		*right;
	void				*content;
	int					fd;
}						t_node;

/*
** These functions switch the lexer states depending on input
** typedef void			(*t_lex_transition)(char, t_lexer *);
** typedef int				(*t_lex_action)(char, t_list **);
*/

typedef struct			s_token
{
	char				*value;
	int					literal;
}						t_oken;

typedef struct			s_lexer
{
	t_lex_state			prev_state;
	t_lex_state			state;
	int					(*actions[LEX_STATES])(struct s_lexer *);
	void				(*transitions[LEX_STATES])(struct s_lexer *);
	t_list				*tokens;
	char				*input;
	size_t				token_start;
	size_t				token_len;

	t_node				*tree;
	t_oken_type			p_token;
	char				**envac;
	t_list				*env_list;
	t_list				*exp_list;
}						t_lexer;

typedef struct			s_env_var
{
	char				*name;
	char				*value;
	int					is_env;
}						t_var;

int						is_white_space(char c);
void					skip_whitespace(char **line);
int						starts_with(const char *input, const char *match);
int						is_name_char(char c);

t_var					*new_env(char *name, char *value, int is_env);

char					*get_pwd();
int						update_pwd(t_list *env_list, char *path);

void					print_env_vars(t_lexer *lex, int env);
t_var					*get_var(t_list *env_list, char *key);

void					remove_var_null(t_list **exp_list, char *key);

int						is_number_n(char *input, int size);
int						get_number(char *input, int size);
int						is_valid_assign_n(char *word, int len);

char					*get_var_value(t_list *env_list, char *key);
int						expand_word(t_lexer *lex, char *word, char **first);
void					filter_word(char *word);
int						treat_word(t_lexer *lex, t_node *node);

void					free_split(char **split);

char					**get_env_list(t_lexer *lex);
int						is_dir(char *name);

int 					*lst_rtn(void);

/*
** Transitions and actions
*/

void					from_general(t_lexer *lex);
void					from_word(t_lexer *lex);
void					from_s_quote(t_lexer *lex);
void					from_d_quote(t_lexer *lex);
void					from_backslash(t_lexer *lex);
void					from_and(t_lexer *lex);
void					from_or(t_lexer *lex);
void					from_semi_colon(t_lexer *lex);
void					from_supp(t_lexer *lex);
void					from_inf(t_lexer *lex);
void					from_error(t_lexer *lex);

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

int						generate_tree(t_lexer *lex);
int						push_token(t_lexer *lex);
char					*get_command_path(char *path_line, char *command);
void					execute_tree(t_lexer *lex, t_node *node);
void					handle_redir(t_lexer *lex, t_node *node);

void					cd_exec(t_lexer *lex, t_node *node);
void					env_exec(t_lexer *lex, t_node *node);
void					pwd_exec(t_lexer *lex, t_node *node);
void					exit_exec(t_lexer *lex, t_node *node);
void					export_exec(t_lexer *lex, t_node *node);
void					unset_exec(t_lexer *lex, t_node *node);
void					echo_exec(t_lexer *lex, t_node *node);

#endif
