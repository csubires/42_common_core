/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:17:46 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:21:54 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **array, int len)
{
	int	x;

	if (!array)
		return ;
	x = 0;
	if (len == -1)
	{
		while (array[x])
		{
			free(array[x]);
			x++;
		}
	}
	else
	{
		while (x < len && array[x])
		{
			free(array[x]);
			x++;
		}
	}
	free(array);
}
