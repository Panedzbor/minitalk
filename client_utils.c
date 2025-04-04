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
