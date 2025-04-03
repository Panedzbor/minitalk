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
void	sigusr1_handler(int sig);
void	sigusr2_handler(int sig);
void	decode_pid(int bit);
void	decode_char(int bit);
void	add_char(int ch);
void	add_first_char(char **str, int ch);
void	print_str(char **str);
void	set_to_null(void **ptr1, void **ptr2);

pid_t	g_client_pid;

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	g_client_pid = 0;
	ft_printf("Server PID: %d\n", pid);
	/*signal(SIGINT, sigint_handler);*/
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	while(true)
		sleep(1);
	return (0);
}

/*void	sigint_handler(int sig)
{
	ft_printf("CTRL + C detected, ending the proces...");
	exit (sig);
}*/
void	sigusr1_handler(int sig)
{
	write(1, "s1\n", 3);
	if (g_client_pid == 0)
		decode_pid(sig * 0);
	else
	{
		decode_char(sig * 0);
		kill(g_client_pid, SIGUSR2);
	}
}

void	sigusr2_handler(int sig)
{
	write(1, "s2\n", 3);
	if (g_client_pid == 0)
		decode_pid(sig * 0);
	else
	{
		decode_char(sig * 0 + 1);
		kill(g_client_pid, SIGUSR2);
	}
}

void	decode_pid(int bit)
{
	static pid_t	temp;
	static int		pos;

	temp += bit << pos;
	pos++;
	if (pos == 23)
	{
		g_client_pid = temp;
		kill(g_client_pid, SIGUSR1);
	}
}

void	decode_char(int bit)
{
	static int	ch;
	static int	pos;

	ch += bit << pos;
	pos++;
	if (pos == 8)
	{
		pos = 0;
		ch = 0;
		add_char(ch);
	}
}

void	add_char(int ch)
{
	static char	*str;
	char		*temp;
	char		*str2;

	set_to_null((void **)&temp, (void **)&str2);
	if (!str)
	{
		add_first_char(&str, ch);
		return ;
	}
	str2 = (char *)ft_calloc(sizeof(char), 2);
	if (!str2)
	{
		free((void *)str);
		exit(-1);
	}
	str2[0] = ch;
	temp = ft_strjoin(str, str2);
	free((void *)str);
	free((void *)str2);
	str = temp;
	set_to_null((void **)&temp, (void **)&str2);
	if (ch == '\0')
		/*process_str(&str);*/
		print_str(&str);
}

/*void	process_str(char **str)
{
	static bool	flag_reading_str;

	if (!flag_reading_str)
	{
		process_client_pid(str);
		flag_reading_str = true;
	}
	else
		print_str(str);
}*/

void	add_first_char(char **str, int ch)
{
	*str = (char *)ft_calloc(sizeof(char), 2);
	if (!(*str))
		exit(-1);
	(*str)[0] = ch;
}

/*void	process_client_pid(char **str)
{
	g_client_pid = ft_atoi(*str);
	free((void *)*str);
	*str = NULL;
	kill(g_client_pid, SIGUSR2);
}*/

void	print_str(char **str)
{
	ft_printf("%s\n", *str);
	free((void *)*str);
	*str = NULL;
}

void	set_to_null(void **ptr1, void **ptr2)
{
	if (*ptr1)
		*ptr1 = NULL;
	if (*ptr2)
		*ptr2 = NULL;
}
