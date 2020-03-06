/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:26:25 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/06 12:39:46 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_options(t_flag_options *options)
{
	options->prefix = 0;
	options->zero_pad = 0;
	options->left_pad = 0;
	options->blank = 0;
	options->signed_ = 0;
	options->grouping = 0;
	options->width = -1;
	options->prec = -1;
}

t_conv	*init_conv(void)
{
	t_conv	*conv;

	if (!(conv = malloc(sizeof(t_conv))))
		return (0);
	if (!(conv->stream = ft_strnew(OUTPUT_INTERVAL)))
		return (0);
	conv->length = 0;
	conv->buf_len = 0;
	conv->ret = 0;
	conv->max = OUTPUT_INTERVAL;
	return (conv);
}

void	free_obj(t_conv *conv)
{
	free(conv->stream);
	free(conv);
}
