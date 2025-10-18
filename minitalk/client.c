/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:44:38 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 20:58:39 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

static void	ft_send_char(int pid, unsigned char c)
{
	unsigned int	bit_pos;

	bit_pos = 8;
	while (bit_pos--)
	{
		if (c >> bit_pos & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
	}
}

static void	ft_send_msg(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, (unsigned char)*str++);
	ft_send_char(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	error;

	if (argc != 3)
	{
		ft_printf(" Enter the arguments correctly: ");
		ft_printf("%s PID \"MSG\"\n", argv[0]);
		return (1);
	}
	ft_send_msg(ft_atoi_err(argv[1], &error), argv[2]);
	return (0);
}
