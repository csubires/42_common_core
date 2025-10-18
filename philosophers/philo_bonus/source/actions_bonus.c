/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:47:38 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	am_i_dead(t_philo *philo)
{
	if ((get_time() - philo->last_time_ate) > philo->time_to_die \
	&& philo->eating == 0)
	{
		show_action(philo, MSG_DEAD);
		philo->i_live = 0;
		return (1);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->req->sem_forks);
	show_action(philo, MSG_TAKE);
	if (philo->req->number_philos == 1)
	{
		ft_usleep(philo, philo->time_to_die + 1);
		return ;
	}
	sem_wait(philo->req->sem_forks);
	show_action(philo, MSG_TAKE);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->req->sem_forks);
	show_action(philo, MSG_DROP);
	sem_post(philo->req->sem_forks);
	show_action(philo, MSG_DROP);
}

void	to_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->req->number_philos == 1)
	{
		drop_forks(philo);
		return ;
	}
	philo->eating = 1;
	show_action(philo, MSG_EAT);
	if (philo->num_must_eat != -42)
		philo->num_must_eat--;
	philo->last_time_ate = get_time();
	ft_usleep(philo, philo->time_to_eat);
	philo->eating = 0;
	drop_forks(philo);
}

void	to_sleep(t_philo *philo)
{
	show_action(philo, MSG_SLEEP);
	ft_usleep(philo, philo->time_to_sleep);
}
