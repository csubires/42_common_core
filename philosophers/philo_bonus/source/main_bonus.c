/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:47:54 by csubires          #+#    #+#             */
/*   Updated: 2024/09/10 17:41:42 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philos(t_requirement *req)
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
		philos[x].time_to_die = req->time_to_die;
		philos[x].time_to_eat = req->time_to_eat;
		philos[x].time_to_sleep = req->time_to_sleep;
		philos[x].num_must_eat = req->num_must_eat;
		philos[x].i_live = 1;
		philos[x].eating = 0;
	}
	return (philos);
}

t_requirement	parse_args(char argc, char *argv[])
{
	t_requirement	require;

	require.one_error = 0;
	require.number_philos = ft_atoi(argv[1]);
	require.time_to_die = ft_atoi(argv[2]);
	require.time_to_eat = ft_atoi(argv[3]);
	require.time_to_sleep = ft_atoi(argv[4]);
	require.num_must_eat = -42;
	if (argc == 6)
		require.num_must_eat = ft_atoi(argv[5]);
	if (!require.number_philos || !require.num_must_eat)
		ft_error(&require, ERR_ZERO);
	return (require);
}

int	check_args(int argc, char *argv[])
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
	t_requirement	req;
	t_philo			*philos;

	philos = 0;
	if (!check_args(argc, argv))
	{
		printf("\33[91m [✖] ERROR: %s\033[0m\n", ERR_ARGS);
		printf("\33[91m%s\033[0m\n", MSG_HELP);
		return (-1);
	}
	req = parse_args(argc, argv);
	if (!req.one_error && activate_sems(&req))
		philos = create_philos(&req);
	if (!req.one_error)
		wake_up_philos(&req, philos);
	free_all(&req, philos);
	return (0);
}
