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

void	send_pid(pid_t pid, pid_t server_pid);
void	sigusr1_handler(int sig);
void	sigusr2_handler(int sig);
void	send_str(pid_t server_pid, char *string);
int		send_bit(int i, int pos, pid_t server_pid, char *string);
void	check_input(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	pid_t	pid;
	pid_t	server_pid;

	g_signal_received = false;
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	check_input(argc, argv);
	pid = getpid();
	server_pid = ft_atoi(argv[1]);
	send_pid(pid, server_pid);
	send_str(server_pid, argv[2]);
	return (0);
}

void	send_pid(pid_t pid, pid_t server_pid)
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
		sleep(2);
		pos++;
	}
}

void	sigusr1_handler(int sig)
{
	write(1, "s1\n", 3);
	g_signal_received = sig * 0 + 1;
}

void	sigusr2_handler(int sig)
{
	write(1, "s2\n", 3);
	g_signal_received = sig * 0 + 1;
}

void	send_str(pid_t server_pid, char *string)
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

int	send_bit(int i, int pos, pid_t server_pid, char *string)
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

void	check_input(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		ft_printf("Invalid number of arguments. Must be two!\n");
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
