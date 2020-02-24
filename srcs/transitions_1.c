/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <lgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:58:10 by lgrellie          #+#    #+#             */
/*   Updated: 2020/02/24 18:58:11 by lgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        lex->state = e_general;
    else if (c == '>')
        lex->state = e_supp;
    else if (c == '<')
        lex->state = e_inf;
    else if (c == ';')
        lex->state = e_semi_colon;
    else if (c == '&')
        lex->state = e_and;
    else if (c == '|')
        lex->state = e_or;
    else
        lex->state = e_word;
}

void        from_word(char c, t_lexer *lex)
{

}

void		from_s_quote(char c, t_lexer *lex)
{

}

void		from_d_quote(char c, t_lexer *lex)
{


}
void					from_backslash(char c, t_lexer *lex);
void					from_and(char c, t_lexer *lex);
void					from_or(char c, t_lexer *lex);
void					from_semi_colon(char c, t_lexer *lex);
void					from_supp(char c, t_lexer *lex);
void					from_inf(char c, t_lexer *lex);
void					from_error(char c, t_lexer *lex);
