/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:52:34 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 18:42:12 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_mod(char *s1, char *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*str_join;

	if (!s2)
		return (0);
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (0);
		s1[0] = '\0';
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str_join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str_join)
	{
		ft_free_ptr(&s1);
		return (0);
	}
	ft_strlcpy(str_join, s1, len_s1 + 1);
	ft_strlcpy(str_join + len_s1, s2, len_s2 + 1);
	ft_free_ptr(&s1);
	return (str_join);
}
