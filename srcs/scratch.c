/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scratch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <lgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:58:00 by lgrellie          #+#    #+#             */
/*   Updated: 2020/02/24 18:58:02 by lgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         push_token(t_lexer *lex)
{
    char    *str;

    str = ft_substr(lex->input, lex->token_start, lex->i - );
}

int         lex_it_(t_lexer *lex)
{
    int     res;

    // if (!(*lex->input))
    // {
    //     if (push_token(lex))
    //     {
            
    //     }
    // }

    if (res = lex->actions[lex->state](lex->input[lex->i], &lex->tokens))
    {
        
    }
    lex->transitions[lex->state](lex->input, lex);
    ++(lex->input);
    return (lex_it_(lex));
}
