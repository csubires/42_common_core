/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:59:24 by csubires          #+#    #+#             */
/*   Updated: 2024/04/22 14:21:21 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			x;

	if (!s1 || !s2 || !n)
		return (0);
	x = 0;
	while (s1[x] && s2[x] && s1[x] == s2[x] && x < (n - 1))
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
