/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:20:23 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:33:42 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define OUTPUT_INTERVAL 256

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

typedef struct		s_flag_options
{
	unsigned int	prefix;
	unsigned int	zero_pad;
	unsigned int	left_pad;
	unsigned int	blank;
	unsigned int	signed_;
	unsigned int	grouping;
	int				width;
	int				prec;
}					t_flag_options;

typedef struct		s_conv
{
	char			buffer[4096];
	int				buf_len;
	char			*stream;
	int				length;
	int				max;
	int				ret;
	t_flag_options	options;
}					t_conv;

int					ft_printf(const char *entry, ...);
int					ft_printf_err(const char *entry, ...);

int					inc_str_len(t_conv *conv);

int					lld_handler(const char **entry, t_conv *conv, va_list ap);
int					ld_handler(const char **entry, t_conv *conv, va_list ap);
int					hhd_handler(const char **entry, t_conv *conv, va_list ap);
int					hd_handler(const char **entry, t_conv *conv, va_list ap);
int					std_handler(const char **entry, t_conv *conv,
								va_list ap, int fd);

int					flag_handler(t_conv *conv, char arg);

void				get_base(long long int num, t_conv *conv);
void				get_base_u(unsigned long long num, t_conv *conv, char arg);

void				shift_left_string(t_conv *conv, int offset);
int					prepend_string(t_conv *conv, const char *pre);
void				append_string(t_conv *conv, const char *ap);
int					left_pad(t_conv *conv, unsigned int amount, char pad);
int					right_pad(t_conv *conv, unsigned int amount, char pad);
void				shave(t_conv *conv, int offset);
int					inject(t_conv *conv, unsigned int amount,
					int index, char cont);

void				safe_strcat_char_arg(t_conv *conv, unsigned char c);
int					safe_strcat_arg(t_conv *conv, const char *str);
int					safe_strcat_char(t_conv *conv, unsigned char c, int fd);

void				flush_stream(t_conv *conv, int fd);
void				flush_buffer(t_conv *conv, int fd);

int					handle_prefix_ox(t_conv *conv, char arg);
void				handle_signed(t_conv *conv, char arg);
void				handle_blank(t_conv *conv, char arg);
int					zero_precision_case(t_conv *conv, char arg);
int					precision_handler(t_conv *conv, char arg, int pre);
int					width_handler(t_conv *conv, int pre);
int					flag_handler(t_conv *conv, char arg);

int					check_precision(const char **entry,
									t_flag_options *options, va_list va);
int					check_field_width(const char **entry,
									t_flag_options *options, va_list va);
int					check_length_modifiers(const char **entry,
											t_conv *conv, va_list va, int fd);
int					check_flags(const char **entry,
								t_flag_options *options, va_list va);

void				init_options(t_flag_options *options);
t_conv				*init_conv(void);
void				free_obj(t_conv *conv);

#endif
