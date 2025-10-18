/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:30:16 by csubires          #+#    #+#             */
/*   Updated: 2024/11/29 10:10:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	indx_delimiter(char *envp, char separator)
{
	int		x;

	x = 0;
	while (envp[x])
	{
		if (envp[x] == separator)
			return (x);
		x++;
	}
	return (0);
}

char	**split_env_item(char *envp, char separator)
{
	char	**one_var;
	char	*tmp_envp;
	int		str_len;
	int		indx;

	one_var = 0;
	tmp_envp = (char *)envp;
	indx = indx_delimiter(tmp_envp, separator);
	if (!indx)
		str_len = ft_strlen(tmp_envp);
	one_var = (char **)ft_calloc(2, sizeof(char *));
	if (!one_var || !tmp_envp || !*tmp_envp)
		return (0);
	if (indx)
		one_var[0] = ft_substr(tmp_envp, 0, indx);
	else
		one_var[0] = ft_substr(tmp_envp, 0, str_len);
	if (indx)
	{
		tmp_envp += ++indx;
		one_var[1] = ft_substr(tmp_envp, 0, ft_strlen(tmp_envp));
	}
	else
		one_var[1] = 0;
	return (one_var);
}

void	free_env_entry(void *entry)
{
	t_envp	*env_item;

	env_item = (t_envp *)entry;
	free(env_item->key);
	env_item->key = 0;
	free(env_item->value);
	env_item->value = 0;
	free(entry);
	entry = 0;
}
