/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:03:45 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/03 14:03:47 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_signal_received;

static void	sigusr2_handler(int sig);
static void	send_pid(pid_t pid, pid_t server_pid);
static void	send_str(pid_t server_pid, char *string);
static int	send_bit(int i, int pos, pid_t server_pid, char *string);

int	main(int argc, char *argv[])
{
	pid_t	pid;
	pid_t	server_pid;

	g_signal_received = false;
	signal(SIGUSR2, sigusr2_handler);
	check_input(argc, argv);
	pid = getpid();
	server_pid = ft_atoi(argv[1]);
	send_pid(pid, server_pid);
	send_str(server_pid, argv[2]);
	return (0);
}

static void	sigusr2_handler(int sig)
{
	g_signal_received = sig * 0 + 1;
}

static void	send_pid(pid_t pid, pid_t server_pid)
{
	int	pos;
	int	bit;

	pos = 0;
	bit = 0;
	while (pos < 23)
	{
		bit = (pid >> pos) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(1000);
		pos++;
	}
}

static void	send_str(pid_t server_pid, char *string)
{
	int	len;
	int	i;
	int	pos;

	len = ft_strlen(string) + 1;
	i = 0;
	while (i < len)
	{
		pos = 0;
		while (pos < 8)
		{
			while (true)
			{
				if (send_bit(i, pos, server_pid, string))
					break ;
			}
			pos++;
		}
		i++;
	}
}

static int	send_bit(int i, int pos, pid_t server_pid, char *string)
{
	int	bit;

	bit = 0;
	if (g_signal_received)
	{
		g_signal_received = false;
		bit = (string[i] >> pos) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		return (1);
	}
	return (0);
}
