/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:16:11 by csubires          #+#    #+#             */
/*   Updated: 2024/09/10 12:36:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_goal(t_requirement *req)
{
	printf("\33[01m\33[92m\n");
	printf("\t[✔] %d Philosopher of %d have eaten \
%d times!\033[0m\n\n", \
	req->goal, req->number_philos, \
	req->num_must_eat);
}

void	*supervise(void *param)
{
	int		x;
	t_philo	*philos;

	philos = (t_philo *)param;
	while (1)
	{
		x = -1;
		while (++x < philos->req->number_philos)
			if (am_i_dead(philos->req, &philos[x]))
				return (0);
		pthread_mutex_lock(&philos->req->mtx_meal);
		if (philos->req->goal == philos->req->number_philos)
		{
			pthread_mutex_unlock(&philos->req->mtx_meal);
			pthread_mutex_lock(&philos->req->mtx_dead);
			philos->req->finish = 1;
			pthread_mutex_unlock(&philos->req->mtx_dead);
			print_goal(philos->req);
			return (0);
		}
		pthread_mutex_unlock(&philos->req->mtx_meal);
	}
	return (0);
}

void	*tasks_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->index_philo % 2 == 0)
		ft_usleep(philo, 10);
	while (!check_dead(philo))
	{
		to_eat(philo);
		to_sleep(philo);
		show_action(philo, MSG_THINK);
	}
	return (0);
}

void	wake_up_philos(t_philo *philos)
{
	int			x;
	pthread_t	observer;

	if (pthread_create(&observer, 0, supervise, philos))
		ft_error(philos->req, ERR_THREAD);
	x = -1;
	while (++x < philos->req->number_philos)
	{
		if (pthread_create(&philos[x].t_id, 0, tasks_philo, &philos[x]))
		{
			ft_error(philos->req, ERR_THREAD);
			break ;
		}
	}
	while (--x >= 0)
	{
		if (pthread_join(philos[x].t_id, 0))
		{
			ft_error(philos->req, ERR_JOIN);
			break ;
		}
	}
	if (pthread_join(observer, 0))
		ft_error(philos->req, ERR_THREAD);
}
