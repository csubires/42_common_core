/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:45:22 by csubires          #+#    #+#             */
/*   Updated: 2024/11/13 11:35:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str_join;

	if (!s2)
		return (0);
	if (!s1)
	{
		s1 = (char *)ft_calloc(1, sizeof(char));
		if (!s1)
			return (0);
		s1[0] = '\0';
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str_join = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!str_join)
		return (0);
	ft_strlcpy(str_join, s1, len_s1 + 1);
	ft_strlcpy(str_join + len_s1, s2, len_s2 + 1);
	return (str_join);
}
