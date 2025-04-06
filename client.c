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

static void	sigusr1_handler(int sig);
static void	sigusr2_handler(int sig);
static void	send_str(pid_t server_pid, char *string);
static int	send_bit(int i, int pos, pid_t server_pid, char *string);

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
	sleep(1);
	return (0);
}

static void	sigusr1_handler(int sig)
{
	static short	count;

	(void)sig;
	g_signal_received = 1;
	count++;
	if (count == 1)
		ft_printf("Connection with server established\n");
	else
		ft_printf("The message has been fully received by the recipient\n");
}

static void	sigusr2_handler(int sig)
{
	(void)sig;
	g_signal_received = 1;
}

static void	send_str(pid_t server_pid, char *string)
{
	int	len;
	int	i;
	int	pos;

	ft_printf("Sending the string...\n");
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
