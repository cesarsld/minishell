#include "minishell.h"


int     lex_it_(t_list **alst, char *input, t_lexer *lex)
{
    int res;

    if (!(*input))
    {

        //CHECK if state can be an end state
    }
    
    if (res = lex->actions[lex->state](alst, *input))
    {

    }
    lex->transitions[lex->state](*input, lex);
    return (lex_it_(alst, input + 1, lex));
}