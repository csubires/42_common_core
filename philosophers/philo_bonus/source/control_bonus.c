/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:47:46 by csubires          #+#    #+#             */
/*   Updated: 2024/09/10 18:11:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (1)
		if (am_i_dead(philo))
			break ;
	return (0);
}

void	tasks_philo(t_philo *philo)
{
	if (philo->index_philo % 2 == 0)
		ft_usleep(philo, 10);
	if (pthread_create(&philo->dead_pid, 0, check_dead, philo))
		ft_error(philo->req, ERR_THREAD);
	while (philo->num_must_eat > 0 || philo->req->num_must_eat == -42)
	{
		if (!philo->i_live)
			exit(1);
		to_eat(philo);
		to_sleep(philo);
		show_action(philo, MSG_THINK);
	}
	if (pthread_join(philo->dead_pid, NULL))
		ft_error(philo->req, ERR_JOIN);
}

void	wake_up_philos(t_requirement *req, t_philo *philos)
{
	int			x;

	x = -1;
	while (++x < req->number_philos && !req->one_error)
	{
		philos[x].start_time = get_time();
		philos[x].last_time_ate = philos[x].start_time;
		philos[x].t_pid = fork();
		if (!philos[x].t_pid)
		{
			tasks_philo(&philos[x]);
			exit(0);
		}
		else if (philos[x].t_pid < 0)
			ft_error(req, ERR_FORK);
	}
	wait_children(philos);
}

void	wait_children(t_philo *philos)
{
	int	x;
	int	status;
	int	goal;

	x = -1;
	goal = 0;
	while (++x < philos->req->number_philos)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			ft_error(philos->req, ERR_WAIT);
			break ;
		}
		if (WIFEXITED(status))
		{
			if (!WEXITSTATUS(status))
				goal++;
			else
				break ;
		}
	}
	while (x++ < philos->req->number_philos)
		kill(philos[x - 1].t_pid, SIGTERM);
	if (goal == philos->req->number_philos)
		print_goal(philos->req, goal);
}
