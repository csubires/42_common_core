/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:12:43 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:59:36 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return ((current.tv_sec * TO_MICROSEG) + (current.tv_usec / TO_MICROSEG));
}

void	ft_usleep(t_philo *philo, unsigned int n)
{
	long	start;

	start = get_time();
	while (!check_dead(philo) && get_time() - start < n)
		usleep(100);
}

void	free_all(t_requirement *req, pthread_mutex_t *forks, t_philo *philos)
{
	if (req)
	{
		pthread_mutex_destroy(&req->mtx_dead);
		pthread_mutex_destroy(&req->mtx_meal);
		pthread_mutex_destroy(&req->mtx_show);
	}
	if (forks)
		free_forks(forks, req->number_philos);
	if (philos)
	{
		free(philos);
		philos = 0;
	}
}

void	free_forks(pthread_mutex_t *forks, int len)
{
	int	x;

	x = -1;
	while (++x < len)
		pthread_mutex_destroy(&forks[x]);
	free(forks);
	forks = 0;
}

void	show_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->req->mtx_show);
	if (!check_dead(philo))
		printf("%ld \33[01m%d\033[0m %s\n", \
			get_time() - philo->start_time, \
			philo->index_philo, action);
	pthread_mutex_unlock(&philo->req->mtx_show);
}
