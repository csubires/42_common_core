/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:51:10 by csubires          #+#    #+#             */
/*   Updated: 2024/11/22 11:57:10 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_strenv(t_dllist *node)
{
	t_envp	*env_item;
	char	*join;

	env_item = (t_envp *)node->data;
	join = ft_strconcat(3, env_item->key, "=", env_item->value);
	return (join);
}

int	is_builtin(char *exec_str)
{
	char	*builtin[8];
	int		x;

	builtin[0] = "cd";
	builtin[1] = "echo";
	builtin[2] = "env";
	builtin[3] = "exit";
	builtin[4] = "export";
	builtin[5] = "pwd";
	builtin[6] = "unset";
	builtin[7] = 0;
	x = 0;
	while (builtin[x])
		if (!ft_strcmp(exec_str, builtin[x++]))
			return (1);
	return (0);
}

char	**args_to_array(t_exec *exec_cmd)
{
	t_dllist	*tmp_list;
	char		**array;
	int			list_len;
	int			x;

	tmp_list = exec_cmd->arg_list;
	list_len = dlist_size(tmp_list);
	array = ft_calloc((list_len + 2), sizeof(char *));
	array[0] = (char *)exec_cmd->executable;
	x = 1;
	while (x <= list_len)
	{
		array[x++] = (char *)tmp_list->data;
		tmp_list = tmp_list->next;
	}
	array[x] = 0;
	return (array);
}

char	**envp_to_array(t_shell *shell)
{
	t_dllist	*tmp_list;
	char		**array;
	size_t		list_len;
	size_t		x;

	x = 0;
	tmp_list = shell->env_list;
	list_len = dlist_size(shell->env_list);
	array = ft_calloc((list_len + 1), sizeof(char *));
	while (x < list_len)
	{
		array[x++] = join_strenv(tmp_list);
		tmp_list = tmp_list->next;
	}
	array[x] = 0;
	return (array);
}
