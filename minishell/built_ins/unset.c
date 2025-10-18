/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:02:14 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 11:08:12 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	buildin_unset(t_shell *shell, t_exec *exec_cmd)
{
	t_dllist	*tmp_list;
	t_dllist	*node;

	shell->exit_stat = 0;
	if (!exec_cmd->arg_list)
		return (0);
	tmp_list = exec_cmd->arg_list;
	while (tmp_list)
	{
		node = search_env_item(shell->env_list, (char *)tmp_list->data);
		if (node)
			dlist_remove(&shell->env_list, node, free_env_entry);
		tmp_list = tmp_list->next;
	}
	return (0);
}
