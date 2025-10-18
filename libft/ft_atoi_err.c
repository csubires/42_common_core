/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:15:08 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 18:30:53 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi_err(const char *str, int *error)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	*error = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' && str++)
		sign = -1;
	else if (*str == '+')
		str++;
	if (!*str)
		*error = 1;
	while (*str && !*error)
	{
		if (!ft_isdigit(*str))
		{
			*error = 1;
			break ;
		}
		result = (result * 10) + ((unsigned char)*str - '0');
		str++;
	}
	return (result * sign);
}
