/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:30:11 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 14:07:08 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			x;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	unsigned char	*tmp_res;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	x = 0;
	tmp_res = tmp_dst;
	while (x++ < n)
		*tmp_dst++ = *tmp_src++;
	return (tmp_res);
}
