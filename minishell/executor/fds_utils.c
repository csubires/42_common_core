/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:36:11 by csubires          #+#    #+#             */
/*   Updated: 2024/11/11 10:26:52 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_fd_flags(int append_to_fd)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (append_to_fd)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static void	manage_input_fd(t_exec *exec_cmd)
{
	int		in_fd;

	if (file_exists(exec_cmd->input_file))
	{
		in_fd = open(exec_cmd->input_file, O_RDONLY);
		if (exec_cmd->in_fd == -1)
		{
			print_error(1, 0, ERR_FD, 0);
			return ;
		}
		else
		{
			if (exec_cmd->in_fd != 0)
				close(exec_cmd->in_fd);
			exec_cmd->in_fd = in_fd;
		}
	}
}

void	manage_output_fd(t_exec *exec_cmd, t_dllist *tmp_list)
{
	t_exec	*next_exec_cmd;
	int		flags;
	int		fd;

	flags = set_fd_flags(exec_cmd->append_to_fd);
	fd = open(exec_cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		print_error(1, 0, ERR_FD, 0);
		return ;
	}
	if (exec_cmd->out_fd != 1)
		close(exec_cmd->out_fd);
	exec_cmd->out_fd = fd;
	if (tmp_list && tmp_list->next)
	{
		next_exec_cmd = tmp_list->next->data;
		if (next_exec_cmd->in_fd != 0)
		{
			close(next_exec_cmd->in_fd);
			next_exec_cmd->in_fd = 0;
		}
	}
}

static void	create_pipe(t_exec *exec_cmd)
{
	int	fds[2];

	if (pipe(fds) != -1)
	{
		if (exec_cmd->heredoc_data)
		{
			write(fds[1], exec_cmd->heredoc_data, \
			ft_strlen(exec_cmd->heredoc_data));
			close(fds[1]);
		}
		if (exec_cmd->in_fd != 0)
			close(exec_cmd->in_fd);
		exec_cmd->in_fd = fds[0];
	}
}

void	manage_heredoc(t_shell *shell)
{
	t_dllist	*tmp_list;
	t_exec		*exec_cmd;

	tmp_list = shell->exec_list;
	while (tmp_list)
	{
		exec_cmd = tmp_list->data;
		if (exec_cmd->heredoc_delimiter)
			create_pipe(exec_cmd);
		if (exec_cmd->input_file)
			manage_input_fd(exec_cmd);
		if (exec_cmd->output_file)
			manage_output_fd(exec_cmd, tmp_list);
		tmp_list = tmp_list->next;
	}
}
