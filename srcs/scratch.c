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

int         lex_it_(t_lexer *lex)
{
    int     res;

    if (res = lex->actions[lex->state](lex))
    {
        
    }
    lex->transitions[lex->state](lex);
    ++(lex->input);
    return (lex_it_(lex));
}
