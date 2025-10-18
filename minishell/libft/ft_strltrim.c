/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strltrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:02:25 by csubires          #+#    #+#             */
/*   Updated: 2024/11/22 12:07:46 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strltrim(char const *s1, char const *s2)
{
	char	*tmp_s1;
	char	*tmp_s2;
	size_t	x;

	if (!s1 || !s2)
		return (0);
	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	if (!ft_strcmp(tmp_s1, tmp_s2))
		return (0);
	x = 0;
	while (*tmp_s1 && *tmp_s2 && (*tmp_s1 == *tmp_s2))
	{
		tmp_s1++;
		tmp_s2++;
		x++;
	}
	if (!tmp_s1 && !tmp_s2)
		return ((char *)s1);
	else if (x == ft_strlen(s2))
		return (tmp_s1);
	else
		return (0);
}
