/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:08:50 by csubires          #+#    #+#             */
/*   Updated: 2024/11/21 10:10:55 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(void *array[])
{
	int	x;

	if (!array)
		return ;
	x = 0;
	while (array[x])
	{
		free(array[x]);
		array[x] = 0;
		x++;
	}
	free(array);
	array = 0;
}

static char	**env_path_to_array(t_shell *shell)
{
	char	*tmp_str;
	char	**path_array;

	tmp_str = get_env_value(shell->env_list, "PATH");
	if (!tmp_str)
		print_error(-1, shell, ERR_PATH, 0);
	path_array = ft_split(tmp_str, ':');
	if (!path_array)
		print_error(1, shell, ERR_PATH, 0);
	return (path_array);
}

char	*get_path_exec(t_shell *shell, char *exec_str)
{
	char	**path_array;
	char	*full_path_bin;
	int		x;

	path_array = env_path_to_array(shell);
	x = 0;
	while (path_array[x])
	{
		full_path_bin = ft_strconcat(3, path_array[x], "/", exec_str);
		if (!full_path_bin)
			print_error(-1, shell, ERR_PATH, 0);
		if (!access(full_path_bin, X_OK))
		{
			free_array((void **)path_array);
			return (full_path_bin);
		}
		free (full_path_bin);
		x++;
	}
	free_array((void **)path_array);
	return (0);
}
