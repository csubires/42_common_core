/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:30:43 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:13:54 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(size_t n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_toa(size_t len, size_t n, char *str)
{
	long long	tmp_n;

	tmp_n = n;
	while (len)
	{
		str[--len] = (tmp_n % 10) + '0';
		tmp_n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = ft_nlen(n * sign);
	if (n <= 0)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	ft_toa(len, n * sign, str);
	if (n < 0)
		str[0] = '-';
	return (str);
}
