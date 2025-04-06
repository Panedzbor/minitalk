/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:41:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/04 15:41:33 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	check_input(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		ft_printf("Invalid number of arguments. Must be two: ./client <serv_pid> <string>\n");
		exit(-1);
	}
	i = 0;
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_printf("The first argument must be server PID.\n");
			exit(-1);
		}
		i++;
	}
}

void	send_pid(pid_t pid, pid_t server_pid)
{
	int	pos;
	int	bit;

	ft_printf("Sending PID to the server...\n");
	pos = 0;
	bit = 0;
	while (pos < 23)
	{
		bit = (pid >> pos) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(2000);
		pos++;
	}
}
