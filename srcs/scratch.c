#include "minishell.h"


int     lex_it_(t_lexer *lex)
{
    int res;

    if (!(*lex->input))
    {

        //CHECK if state can be an end state
    }

    if (res = lex->actions[lex->state](lex->input, &lex->tokens))
    {
        
    }
    lex->transitions[lex->state](*lex->input, lex);
    ++(lex->input);
    return (lex_it_(lex));
}