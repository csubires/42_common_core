/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:46:57 by csubires          #+#    #+#             */
/*   Updated: 2024/11/28 16:36:30 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_path(char *str)
{
	if (ft_strchr(str, '/') && (str[0] == '/' || str[0] == '.'))
		return (1);
	return (0);
}

static void	dump_fds(t_exec *exec_cmd[])
{
	if ((*exec_cmd)->in_fd != 0)
	{
		dup2((*exec_cmd)->in_fd, 0);
		close((*exec_cmd)->in_fd);
	}
	if ((*exec_cmd)->out_fd != 1)
	{
		dup2((*exec_cmd)->out_fd, 1);
		close((*exec_cmd)->out_fd);
	}
}

void	execute_child(t_shell *shell, char **env, char **arg, t_exec *exec_cmd)
{
	char	*path;

	if ((exec_cmd->input_file && !file_exists(exec_cmd->input_file)) || \
		exec_cmd->in_fd == -1)
	{
		print_error(1, shell, ERR_FD, 0);
		return ;
	}
	if (has_path(arg[0]))
	{
		path = ft_strdup(arg[0]);
		if (!path)
			print_error(-1, shell, ERR_CHILD, arg[0]);
	}
	else
		path = get_path_exec(shell, arg[0]);
	if (!path)
	{
		shell->exit_stat = 1;
		print_error(-1, shell, ERR_NOTCMD, arg[0]);
	}
	dump_fds(&exec_cmd);
	execve(path, arg, env);
	print_error(-1, shell, ERR_CHILD, arg[0]);
	exit (1);
}
