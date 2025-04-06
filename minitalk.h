/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:56:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/01 13:56:37 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/types.h>
#include <signal.h>

void	add_char(int ch, pid_t *client_pid);
void	check_input(int argc, char *argv[]);
void	send_pid(pid_t pid, pid_t server_pid);
