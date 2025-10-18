/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:56 by csubires          #+#    #+#             */
/*   Updated: 2024/09/06 13:19:28 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isspace(char c)
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

void	free_all(t_requirement *req, t_philo *philos)
{
	if (!req->one_error)
	{
		sem_close(req->sem_forks);
		sem_close(req->sem_show);
	}
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SHOW);
	free(philos);
	philos = 0;
}

int	ft_error(t_requirement *req, char *msg)
{
	req->one_error = 1;
	printf("\33[91m [✖] ERROR: %s\033[0m\n", msg);
	return (-1);
}
