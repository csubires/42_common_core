/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:30:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 18:41:35 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa_mod(int n)
{
	long long	tmp_n;
	int			len;
	int			sign;
	char		*arr_str;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp_n = (long long)n * sign;
	len = ft_nbrlen(tmp_n);
	arr_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr_str)
		return (0);
	arr_str = convert(tmp_n, arr_str, len, sign);
	return (arr_str);
}
