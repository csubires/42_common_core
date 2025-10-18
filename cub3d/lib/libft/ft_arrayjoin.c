/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:50 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:33:09 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**no_old(char *new_str)
{
	char	**new_array;

	new_array = malloc(2 * sizeof(char *));
	if (!new_array)
		return (0);
	new_array[0] = new_str;
	new_array[1] = 0;
	return (new_array);
}

char	**ft_arrayjoin(char **old, char *new_str)
{
	char	**new_array;
	int		len_old;
	int		i;

	if (!new_str)
		return (old);
	if (!old)
		return (no_old(new_str));
	len_old = ft_strslen(old);
	new_array = malloc((len_old + 2) * sizeof(char *));
	if (!new_array)
	{
		ft_free_array(old, -1);
		return (0);
	}
	i = -1;
	while (++i < len_old)
		new_array[i] = old[i];
	new_array[i] = new_str;
	new_array[i + 1] = 0;
	free(old);
	return (new_array);
}
