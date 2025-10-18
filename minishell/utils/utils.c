/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:45:19 by csubires          #+#    #+#             */
/*   Updated: 2024/11/28 21:53:43 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isspace(*str++))
			return (0);
	return (1);
}

int	print_error(int err, t_shell *shell, char *msg, char *func)
{
	ft_fdprint(2, "minishell: %s: %s", func, msg);
	if (shell)
	{
		shell->error = 1;
		if (!func)
			shell->exit_stat = 1;
		else
			shell->exit_stat = 127;
	}
	if (err == -1)
		exit (shell->exit_stat);
	return (err);
}

int	file_exists(char *file_name)
{
	struct stat	buffer;

	return (!stat(file_name, &buffer));
}

void	check_args(int argc, char *envp[])
{
	if (!*envp)
	{
		ft_fdprint(2, "minishell: %s", ERR_EVNOTF);
		exit (1);
	}
	if (argc != 1)
	{
		ft_fdprint(2, "minishell: %s", ERR_MANY);
		exit (0);
	}
}
