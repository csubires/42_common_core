/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:46:38 by csubires          #+#    #+#             */
/*   Updated: 2024/08/30 18:30:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*create_forks(t_requirement *req)
{
	pthread_mutex_t	*forks;
	int				x;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* req->number_philos);
	if (!forks)
		ft_error(req, ERR_MALLOC);
	x = -1;
	while (++x < req->number_philos)
	{
		if (pthread_mutex_init(&forks[x], 0))
		{
			free_forks(forks, x);
			ft_error(req, ERR_MUTEX);
		}
	}
	return (forks);
}

t_philo	*create_philos(t_requirement *req, pthread_mutex_t *forks)
{
	t_philo		*philos;
	int			x;

	philos = (t_philo *)malloc(sizeof(t_philo) * req->number_philos);
	if (!philos)
	{
		ft_error(req, ERR_MALLOC);
		return (0);
	}
	x = -1;
	while (++x < req->number_philos)
	{
		philos[x].req = req;
		philos[x].index_philo = x + 1;
		philos[x].food_in_stomach = 0;
		philos[x].mtx_left_fork = &forks[x];
		philos[x].mtx_right_fork = &forks[(x + 1) % req->number_philos];
		philos[x].eating = 0;
		philos[x].start_time = get_time();
		philos[x].last_time_ate = get_time();
	}
	return (philos);
}

t_requirement	parse_args(char argc, char *argv[])
{
	t_requirement	require;

	require.number_philos = ft_atoi(argv[1]);
	require.time_to_die = ft_atoi(argv[2]);
	require.time_to_eat = ft_atoi(argv[3]);
	require.time_to_sleep = ft_atoi(argv[4]);
	require.goal = 0;
	require.finish = 0;
	require.num_must_eat = -42;
	if (argc == 6)
		require.num_must_eat = ft_atoi(argv[5]);
	if (!require.number_philos || !require.num_must_eat)
		ft_error(&require, ERR_ZERO);
	if (pthread_mutex_init(&require.mtx_dead, 0))
		ft_error(&require, ERR_MUTEX);
	if (pthread_mutex_init(&require.mtx_meal, 0))
		ft_error(&require, ERR_MUTEX);
	if (pthread_mutex_init(&require.mtx_show, 0))
		ft_error(&require, ERR_MUTEX);
	return (require);
}

static int	check_args(int argc, char *argv[])
{
	int	x;
	int	y;

	if (argc < 5 || argc > 6)
		return (0);
	x = 0;
	while (++x < argc)
	{
		y = 0;
		while (argv[x][y])
			if (!ft_isdigit(argv[x][y++]))
				return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_requirement	req;

	philos = 0;
	forks = 0;
	if (!check_args(argc, argv))
	{
		printf("\33[91m [✖] ERROR: %s\033[0m\n", ERR_ARGS);
		printf("\33[91m%s\033[0m\n", MSG_HELP);
		return (-1);
	}
	req = parse_args(argc, argv);
	if (!req.finish)
		forks = create_forks(&req);
	if (!req.finish)
		philos = create_philos(&req, forks);
	if (!req.finish)
		wake_up_philos(philos);
	free_all(&req, forks, philos);
	return (0);
}
