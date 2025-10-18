/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:45:46 by csubires          #+#    #+#             */
/*   Updated: 2024/06/04 18:13:13 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen_2(long long n, int sign)
{
	unsigned int	x;

	x = 0;
	if (n == 0)
		x++;
	while (n > 0)
	{
		n /= 10;
		x++;
	}
	if (sign == -1)
		x++;
	return (x);
}

static char	*convert(long long n, char *arr_str, int len, int sign)
{
	arr_str[len--] = '\0';
	if (n == 0)
		arr_str[len--] = '0';
	while (n > 0)
	{
		arr_str[len--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		arr_str[len] = '-';
	return (arr_str);
}

static char	*ft_itoa_2(int n)
{
	long long	tmp_n;
	int			len;
	int			sign;
	char		*arr_str;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp_n = (long long)n * sign;
	len = ft_nbrlen_2(tmp_n, sign);
	arr_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr_str)
		return (0);
	arr_str = convert(tmp_n, arr_str, len, sign);
	return (arr_str);
}

int	ft_putnbr_fd(int n, int fd)
{
	int		len_nbr;
	char	*res;

	res = ft_itoa_2(n);
	if (!res)
		return (-1);
	len_nbr = ft_putstr_fd(res, fd);
	free (res);
	return (len_nbr);
}
