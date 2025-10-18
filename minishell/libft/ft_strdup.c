/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:48:56 by csubires          #+#    #+#             */
/*   Updated: 2024/11/22 11:05:41 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1) + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len);
	return (str);
}
