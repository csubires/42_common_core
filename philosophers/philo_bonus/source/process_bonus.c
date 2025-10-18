/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:41:17 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:59:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (philo->i_live && get_time() - start < n)
		usleep(100);
}

int	activate_sems(t_requirement *req)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SHOW);
	req->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, req->number_philos);
	req->sem_show = sem_open(SEM_SHOW, O_CREAT, S_IRWXU, 1);
	if (req->sem_forks != SEM_FAILED && req->sem_show != SEM_FAILED)
		return (1);
	ft_error(req, ERR_SEM);
	return (0);
}

void	print_goal(t_requirement *req, int goal)
{
	printf("\33[01m\33[92m\n");
	printf("\t[✔] %d Philosopher of %d have eaten %d times!\033[0m\n\n", \
	goal, req->number_philos, req->num_must_eat);
}

void	show_action(t_philo *philo, char *msg)
{
	suseconds_t	timestamp;

	if (!philo->num_must_eat || !philo->i_live)
		return ;
	sem_wait(philo->req->sem_show);
	timestamp = get_time() - philo->start_time;
	printf("%ld \33[01m%d\033[0m %s\n", timestamp, \
	philo->index_philo, msg);
	sem_post(philo->req->sem_show);
}
