/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:32:16 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/01 13:59:43 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <string.h>

int		is_white_space(char c);
void	skip_whitespace(char **line);
int		print_ouput(char *out);

void    pwd_error();
char    *get_pwd();

int get_cd(const char *dir);
void cd_error(const char *dir);
void cd_pwd_error(char *dir);
void cd_dir_error(char * err, const char *dir);

# endif