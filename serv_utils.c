/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:30:04 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/04 15:30:06 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	add_first_char(char **str, int ch);
static void	print_str(char **str, pid_t *client_pid);
static void	set_to_null(void **ptr1, void **ptr2);

void	add_char(int ch, pid_t *client_pid)
{
	static char	*str;
	char		*temp;
	char		*str2;

	temp = NULL;
	str2 = NULL;
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
		print_str(&str, client_pid);
}

static void	add_first_char(char **str, int ch)
{
	*str = (char *)ft_calloc(sizeof(char), 2);
	if (!(*str))
		exit(-1);
	(*str)[0] = ch;
}

static void	print_str(char **str, pid_t *client_pid)
{
	ft_printf("%s\n", *str);
	free((void *)*str);
	*str = NULL;
	*client_pid = 0;
}

static void	set_to_null(void **ptr1, void **ptr2)
{
	if (*ptr1)
		*ptr1 = NULL;
	if (*ptr2)
		*ptr2 = NULL;
}
