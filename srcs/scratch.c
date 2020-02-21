#include "minishell.h"


int     lex_it_(t_list **tokens, char *input, t_lexer *lex)
{
    int res;

    if (!(*input))
    {

        //CHECK if state can be an end state
    }

    if (res = lex->actions[lex->state](*input, tokens))
    {
        
    }
    lex->transitions[lex->state](*input, lex);
    return (lex_it_(tokens, input + 1, lex));
}