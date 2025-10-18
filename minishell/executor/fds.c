/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:30:30 by csubires          #+#    #+#             */
/*   Updated: 2024/11/28 20:02:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_pipe(t_shell *shell)
{
	t_dllist	*tmp_list;
	t_exec		*exec_cmd;
	t_exec		*next_exec_cmd;
	int			fd[2];

	tmp_list = shell->exec_list;
	while (tmp_list && tmp_list->next)
	{
		pipe(fd);
		exec_cmd = tmp_list->data;
		next_exec_cmd = tmp_list->next->data;
		exec_cmd->out_fd = fd[1];
		next_exec_cmd->in_fd = fd[0];
		tmp_list = tmp_list->next;
	}
}

void	manage_fds(t_shell *shell)
{
	if (shell->num_of_cmds > 1)
		set_pipe(shell);
	manage_heredoc(shell);
}
