/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:40:15 by cjaimes           #+#    #+#             */
/*   Updated: 2020/03/02 18:07:50 by cjaimes          ###   ########.fr       */
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

	return (0);
}