#include "minishell.h"


int     lex_it_(t_lexer *lex)
{
    int res;

    if (!(*lex->input))
    {
        if (push_token(lex))
        {

        }
    }

    if (res = lex->actions[lex->state](lex->input[lex->i], &lex->tokens))
    {
        
    }
    lex->transitions[lex->state](lex->input, lex);
    ++(lex->input);
    return (lex_it_(lex));
}