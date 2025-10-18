/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:36:59 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 12:59:54 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n, int *neg)
{
	int	x;

	x = 0;
	*neg = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		x++;
		*neg *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

char	*ft_strrev(char *str)
{
	int		x;
	int		len;
	char	tmp;

	x = 0;
	len = ft_strlen(str) - 1;
	while (x <= ((len - 1) / 2))
	{
		tmp = str[len - x];
		str[len - x] = str[x];
		str[x] = tmp;
		x++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		x;
	int		neg;

	x = 0;
	neg = 0;
	str = (char *)malloc(sizeof(char) * (ft_nbrlen(n, &neg) + 1));
	if (!str)
		return (0);
	if (n == 0)
		str[x++] = '0';
	while (n != 0)
	{
		str[x++] = ((n % 10) * neg) + '0';
		n /= 10;
	}
	if (neg == -1)
		str[x++] = '-';
	str[x] = '\0';
	return (ft_strrev(str));
}

static int	ft_unbrlen(unsigned int n)
{
	int	x;

	x = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		x;

	x = 0;
	str = (char *)malloc(sizeof(char) * (ft_unbrlen(n) + 1));
	if (!str)
		return (0);
	if (n == 0)
		str[x++] = '0';
	while (n != 0)
	{
		str[x++] = (n % 10) + '0';
		n /= 10;
	}
	str[x] = '\0';
	return (ft_strrev(str));
}
