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
    ft_lstadd_back(&(lex->tokens), token);
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
	if (lex->token_len)
		return (push_token(lex));
	else if (is_white_space(lex->input[lex->token_start + lex->token_len]) ||
			!lex->input[lex->token_start + lex->token_len])
		return (discard_one(lex));
	return (0);
}

int			act_word(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf || lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_s_quote(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf || lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_d_quote(t_lexer *lex)
{
	if (lex->prev_state == e_supp || lex->prev_state == e_inf || lex->prev_state == e_or || lex->prev_state == e_and)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	return (0);
}

int			act_backslash(t_lexer *lex)
{
	grow_token(lex);
	return (0);
}

int			act_and(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	discard_one(lex);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}

int			act_or(t_lexer *lex)
{
	if (lex->token_len && lex->prev_state != e_or)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (lex->prev_state == e_or)
	{
		if (push_token(lex))
			return (1);
		lex->state = e_general;
	}
	return (0);
}

int			act_semi_colon(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}

int			act_supp(t_lexer *lex)
{
	if (lex->token_len && lex->prev_state != e_supp &&
		is_number_n(lex->input + lex->token_start, lex->token_len))
	{
		grow_token(lex);
		return (0);
	}
	else if (lex->token_len && lex->prev_state != e_supp)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (lex->prev_state == e_supp)
	{
		if (push_token(lex))
			return (1);
		lex->state = e_general;
	}
	return (0);
}

int			act_inf(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}

int			act_error(t_lexer *lex)
{
	if (lex->token_len)
		if (push_token(lex))
			return (1);
	grow_token(lex);
	if (push_token(lex))
		return (1);
	return (0);
}
