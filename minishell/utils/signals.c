/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:41 by csubires          #+#    #+#             */
/*   Updated: 2024/11/28 12:36:39 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	manage_sigint(int sig)
{
	(void)sig;
	if (isatty(0))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	manage_sigquit(int sig)
{
	(void)sig;
	if (isatty(0))
		signal(3, SIG_IGN);
}

void	init_signals(void)
{
	signal(2, manage_sigint);
	signal(3, manage_sigquit);
}

void	restore_signals(void)
{
	signal(2, SIG_DFL);
	signal(3, SIG_DFL);
}
