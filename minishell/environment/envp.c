/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:01:29 by csubires          #+#    #+#             */
/*   Updated: 2024/11/29 09:14:05 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_env_item(t_shell *shell, t_envp *item)
{
	t_dllist	*node;

	if (!item)
		return ;
	node = dlist_new(item);
	if (!node)
		return ;
	dlist_add_after(&shell->env_list, node);
}

t_envp	*create_env_item(char *key_value[])
{
	t_envp	*env_entry;

	env_entry = ft_calloc(1, sizeof(t_envp));
	if (!env_entry)
	{
		free_array((void **)key_value);
		return (0);
	}
	env_entry->key = key_value[0];
	env_entry->value = key_value[1];
	return (env_entry);
}

void	envp_to_dllist(t_shell *shell, char *envp[])
{
	char	**one_var;
	t_envp	*env_item;

	while (*envp)
	{
		one_var = split_env_item(*envp++, '=');
		if (one_var)
		{
			env_item = create_env_item(one_var);
			if (env_item)
				insert_env_item(shell, env_item);
		}
		free(one_var);
	}
}

t_dllist	*search_env_item(t_dllist *env_list, char *key)
{
	t_dllist	*tmp_lst;
	t_envp		*env_item;

	if (!key || !env_list)
		return (0);
	tmp_lst = env_list;
	while (tmp_lst)
	{
		env_item = (t_envp *)tmp_lst->data;
		if (env_item && !ft_strcmp(env_item->key, key))
			return (tmp_lst);
		tmp_lst = tmp_lst->next;
	}
	return (0);
}

char	*get_env_value(t_dllist *env_list, char *key)
{
	t_dllist	*tmp_lst;
	t_envp		*env_item;

	tmp_lst = search_env_item(env_list, key);
	if (!tmp_lst)
		return (0);
	env_item = (t_envp *)tmp_lst->data;
	return (env_item->value);
}
