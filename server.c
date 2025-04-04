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

static void	sigusr1_handler(int sig);
static void	sigusr2_handler(int sig);
static void	decode_pid(int bit);
static void	decode_char(int bit);

pid_t	g_client_pid;

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	g_client_pid = 0;
	ft_printf("Server PID: %d\n", pid);
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	while (true)
		usleep(1000);
	return (0);
}

static void	sigusr1_handler(int sig)
{
	if (g_client_pid == 0)
		decode_pid(sig * 0);
	else
	{
		decode_char(sig * 0);
		if (g_client_pid != 0)
			kill(g_client_pid, SIGUSR2);
	}
}

static void	sigusr2_handler(int sig)
{
	if (g_client_pid == 0)
		decode_pid(sig * 0 + 1);
	else
	{
		decode_char(sig * 0 + 1);
		if (g_client_pid != 0)
			kill(g_client_pid, SIGUSR2);
	}
}

static void	decode_pid(int bit)
{
	static pid_t	temp;
	static int		pos;

	temp += (bit << pos);
	pos++;
	if (pos == 23)
	{
		g_client_pid = temp;
		kill(g_client_pid, SIGUSR2);
		temp = 0;
		pos = 0;
	}
}

static void	decode_char(int bit)
{
	static int	ch;
	static int	pos;

	ch += bit << pos;
	pos++;
	if (pos == 8)
	{
		add_char(ch, &g_client_pid);
		ch = 0;
		pos = 0;
	}
}
