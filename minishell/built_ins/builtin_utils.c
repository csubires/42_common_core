/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:55:43 by csubires          #+#    #+#             */
/*   Updated: 2024/11/15 12:04:47 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_copy_list(t_dllist *dllist)
{
	t_dllist	*tmp_list;

	while (dllist)
	{
		tmp_list = dllist;
		dllist = dllist->next;
		free(tmp_list);
	}
}

void	update_envp(t_dllist *node, char *value)
{
	t_envp	*env_item;

	if (!node)
		return ;
	env_item = (t_envp *)node->data;
	if (env_item->value)
		free(env_item->value);
	env_item->value = value;
	if (value)
	{
		env_item->value = ft_strdup(value);
		if (!env_item->value)
			print_error(-1, 0, ERR_UP_ENV, 0);
	}
	else
		env_item->value = 0;
}
