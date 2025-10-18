/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:44:38 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 20:58:35 by csubires         ###   ########.fr       */
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

static void	ft_confirm(int sig_usr)
{
	if (sig_usr == SIGUSR2)
		ft_printf("SU2, ");
	else if (sig_usr == SIGUSR1)
		ft_printf("SU1, ");
	else
		ft_printf("SU?, ");
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					error;

	if (argc != 3)
	{
		ft_printf(" Enter the arguments correctly: ");
		ft_printf("%s PID \"MSG\"\n", argv[0]);
		return (1);
	}
	sa.sa_handler = ft_confirm;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("Received: ");
	ft_send_msg(ft_atoi_err(argv[1], &error), argv[2]);
	return (0);
}
