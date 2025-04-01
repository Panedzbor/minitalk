/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:45:29 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/01 13:45:30 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sigint_handler(int sig);

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal(SIGINT, sigint_handler);
	while(true)
		sleep(1);
    return (0);
}

void	sigint_handler(int sig)
{
	ft_printf("CTRL + C detected, ending the proces...");
	exit (sig);
}
