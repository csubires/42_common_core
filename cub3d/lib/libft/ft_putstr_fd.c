/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:31:21 by csubires          #+#    #+#             */
/*   Updated: 2024/06/04 18:16:38 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	unsigned int	x;
	int				tmp;

	if (!s)
	{
		tmp = ft_putstr_fd("(null)", fd);
		if (tmp == -1)
			return (-1);
		return (tmp);
	}
	x = 0;
	while (s[x])
	{
		if (ft_putchar_fd((unsigned char)s[x], fd) == -1)
			return (-1);
		x++;
	}
	return (x);
}
