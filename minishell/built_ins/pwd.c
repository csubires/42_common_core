/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:17:31 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 11:18:52 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	buildin_pwd(t_shell *shell, t_exec *exec_cmd)
{
	ft_fdprint(exec_cmd->out_fd, "%s\n", get_env_value(shell->env_list, "PWD"));
	shell->exit_stat = 0;
	return (0);
}
