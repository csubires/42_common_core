/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:46:59 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:20 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_dead(t_requirement *req, t_philo *philo)
{
	pthread_mutex_lock(&req->mtx_meal);
	if ((get_time() - philo->last_time_ate) > req->time_to_die \
	&& philo->eating == 0)
	{
		pthread_mutex_unlock(&req->mtx_meal);
		show_action(philo, MSG_DEAD);
		pthread_mutex_lock(&req->mtx_dead);
		req->finish = 1;
		pthread_mutex_unlock(&req->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(&req->mtx_meal);
	return (0);
}

void	take_forks(t_philo *philo)
{
	if (philo->req->number_philos == 1)
	{
		show_action(philo, MSG_TAKE);
		ft_usleep(philo, philo->req->time_to_die + 1);
		return ;
	}
	if (philo->mtx_right_fork > philo->mtx_left_fork)
	{
		pthread_mutex_lock(philo->mtx_right_fork);
		show_action(philo, MSG_TAKE);
		pthread_mutex_lock(philo->mtx_left_fork);
		show_action(philo, MSG_TAKE);
	}
	else
	{
		pthread_mutex_lock(philo->mtx_left_fork);
		show_action(philo, MSG_TAKE);
		pthread_mutex_lock(philo->mtx_right_fork);
		show_action(philo, MSG_TAKE);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->mtx_right_fork > philo->mtx_left_fork)
	{
		pthread_mutex_unlock(philo->mtx_left_fork);
		show_action(philo, MSG_DROP);
		pthread_mutex_unlock(philo->mtx_right_fork);
		show_action(philo, MSG_DROP);
	}
	else
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		show_action(philo, MSG_DROP);
		pthread_mutex_unlock(philo->mtx_left_fork);
		show_action(philo, MSG_DROP);
	}
}

void	to_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->req->number_philos == 1)
		return ;
	philo->eating = 1;
	pthread_mutex_lock(&philo->req->mtx_meal);
	philo->food_in_stomach++;
	if (philo->req->num_must_eat != -42 && \
	philo->food_in_stomach == philo->req->num_must_eat)
		philo->req->goal++;
	pthread_mutex_unlock(&philo->req->mtx_meal);
	show_action(philo, MSG_EAT);
	philo->last_time_ate = get_time();
	ft_usleep(philo, philo->req->time_to_eat);
	philo->eating = 0;
	drop_forks(philo);
}

void	to_sleep(t_philo *philo)
{
	show_action(philo, MSG_SLEEP);
	ft_usleep(philo, philo->req->time_to_sleep);
}
