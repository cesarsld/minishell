/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:40:15 by cjaimes           #+#    #+#             */
/*   Updated: 2020/02/19 17:37:42 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

void unkillable(int sig)
{
	sig = 0;
	printf("I can't be killed muahaha >:D\n");
}

int main()
{
	// signal(SIGINT, &unkillable);
	// signal(SIGQUIT, &unkillable);
	// signal(SIGKILL, &unkillable);
	printf("Hello World!\n");
	while (1)
		;
	return (0);
}