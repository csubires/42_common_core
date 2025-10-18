/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:47:25 by csubires          #+#    #+#             */
/*   Updated: 2024/08/29 18:57:15 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	unsigned int	x;
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	x = 0;
	while (str[x] && ft_isspace(str[x]))
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	while (str[x] && ft_isdigit(str[x]))
	{
		result = (result * 10) + (str[x] - '0');
		x++;
	}
	return (result * sign);
}

int	ft_error(t_requirement *req, char *msg)
{
	req->finish = 1;
	printf("\n\33[91m [✖] ERROR: %s\033[0m\n", msg);
	return (-1);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->req->mtx_dead);
	if (philo->req->finish == 1)
	{
		pthread_mutex_unlock(&philo->req->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->req->mtx_dead);
	return (0);
}
