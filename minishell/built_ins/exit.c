/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:01:46 by csubires          #+#    #+#             */
/*   Updated: 2024/11/25 11:17:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	buildin_exit(t_shell *shell, t_exec *exec_cmd)
{
	char	*tmp_str;

	if (exec_cmd->arg_list)
	{
		tmp_str = (char *)exec_cmd->arg_list->data;
		if (!ft_isallalpha(tmp_str))
			shell->exit_stat = ft_atoi(tmp_str);
		else
			print_error(1, 0, ERR_EXIT, "exit");
	}
	exit(shell->exit_stat);
}
