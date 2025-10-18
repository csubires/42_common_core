/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_from.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:55:14 by csubires          #+#    #+#             */
/*   Updated: 2025/03/21 07:56:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_from(char *line, int start)
{
	char	*path;
	int		x;

	x = 0;
	while (line[start] && line[start] == ' ')
		start++;
	path = (char *)malloc(sizeof(char) * (ft_strlen(line) - start + 1));
	if (!path)
		return (0);
	while (line[start] && line[start] != '\n' && line[start] != ' ')
		path[x++] = line[start++];
	path[x] = 0;
	return (path);
}
