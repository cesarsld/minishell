#include "minishell.h"

void		from_general(char c, t_lexer *lex)
{
    lex->prev_state = e_general;
    if (c == '\'')
        lex->state = e_s_quote;
    else if (c == '"')
        lex->state = e_d_quote;
    else if (c == '\\')
        lex->state = e_backslash;
    else if (is_white_space(c))
        lex->state = 
}

void		from_s_quote(char c, t_lexer *lex)
{

}

void		from_d_quote(char c, t_lexer *lex)
{


}
void					from_backslash(char c, t_lexer *lex);
void					from_in_and(char c, t_lexer *lex);
void					from_in_or(char c, t_lexer *lex);
void					from_in_semi_colon(char c, t_lexer *lex);
void					from_in_redir_supp(char c, t_lexer *lex);
void					from_in_redir_inf(char c, t_lexer *lex);
void					from_error(char c, t_lexer *lex);