/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:40:31 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 11:19:00 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			x;
	unsigned char	*tmp_b;

	tmp_b = (unsigned char *)b;
	x = 0;
	while (x < len)
		tmp_b[x++] = (unsigned char)c;
	return (b);
}
