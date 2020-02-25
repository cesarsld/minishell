#include "minishell.h"

int         push_token(t_lexer *lex)
{
    char    *str;
    t_list  *token;
    if (lex->token_len == 0)
        return (0);
    if (!(str = ft_substr(lex->input, lex->token_start, lex->token_len)))
        return (1);
    if (!(token = ft_lstnew(str)))
    {
        free(str);
        return(1);
    }
    ft_lstadd_back(lex->tokens, token);
    lex->token_start += ft_strlen(str);
    lex->token_len = 0;
    return (0);
}

int         discard_one(t_lexer *lex)
{
    lex->token_start += 1;
    lex->token_len = 0;
    return (0);
}

int         grow_token(t_lexer *lex)
{
    lex->token_len += 1;
    return (0);
}

int			act_general(t_lexer *lex)
{
    
}

int			act_word(t_lexer *lex)
{

}

int			act_s_quote(t_lexer *lex)
{

}

int			act_d_quote(t_lexer *lex)
{

}

int			act_backslash(t_lexer *lex)
{

}

int			act_and(t_lexer *lex)
{

}

int			act_or(t_lexer *lex)
{

}

int			act_semi_colon(t_lexer *lex)
{

}

int			act_supp(t_lexer *lex)
{

}

int			act_inf(t_lexer *lex)
{

}

int			act_error(t_lexer *lex)
{

}
