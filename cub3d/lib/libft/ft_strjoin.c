/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:52:34 by csubires          #+#    #+#             */
/*   Updated: 2024/04/16 16:00:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str_join;
	unsigned int	len_s1;
	unsigned int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str_join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str_join)
		return (0);
	ft_memcpy(str_join, s1, len_s1);
	ft_memcpy((str_join + len_s1), s2, len_s2);
	str_join[len_s1 + len_s2] = '\0';
	return (str_join);
}
