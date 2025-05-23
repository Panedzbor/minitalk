/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:19:34 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/09 21:44:58 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c == ' ')
		return (16384);
	else if ((c > ' ' && c < '0') || (c > '9' && c < 'A')
		|| (c > 'Z' && c < 'a') || (c > 'z' && c < 127))
		return (16384);
	else if (c >= '0' && c <= '9')
		return (16384);
	else if (c >= 'A' && c <= 'Z')
		return (16384);
	else if (c >= 'a' && c <= 'z')
		return (16384);
	else
		return (0);
}
