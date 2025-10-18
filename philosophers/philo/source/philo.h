/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:47:11 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:49 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <memory.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TO_MICROSEG 1000

# define ERR_ARGS "Invalid arguments. Enter positive numbers"
# define ERR_ZERO "nbr_of_philosophers and num_must_eat must be greater than 0"
# define ERR_THREAD "Failed to create a thread"
# define ERR_JOIN "Failed to join a thread"
# define ERR_MALLOC "Failed to allocate memory"
# define ERR_MUTEX "Failed to initialize mutex"
# define MSG_HELP "\033[38;5;208m Use:\033[0m ./philo \33[93mnumber_of_philosophers \
time_to_die time_to_eat time_to_sleep \
\033[38;5;208m[number_of_times_each_philosopher_must_eat]\033[0m"

# define MSG_TAKE "\33[93mhas taken a fork\033[0m"
# define MSG_DROP "\033[38;5;208mhas dropped a fork\033[0m"
# define MSG_EAT "\33[92mis eating\033[0m"
# define MSG_THINK "\33[96mis thinking\033[0m"
# define MSG_SLEEP "\033[38;5;99mis sleeping\033[0m"
# define MSG_DEAD "\33[91mdied\033[0m"

typedef struct s_requirement
{
	int					number_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	int					goal;
	int					finish;
	pthread_mutex_t		mtx_show;
	pthread_mutex_t		mtx_dead;
	pthread_mutex_t		mtx_meal;
}	t_requirement;

typedef struct s_philo
{
	pthread_t			t_id;
	int					index_philo;
	int					food_in_stomach;
	int					eating;
	suseconds_t			start_time;
	suseconds_t			last_time_ate;
	pthread_mutex_t		*mtx_right_fork;
	pthread_mutex_t		*mtx_left_fork;
	t_requirement		*req;
}	t_philo;

//	ACTIONS.C
int				am_i_dead(t_requirement *req, t_philo *philo);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			to_eat(t_philo *philo);
void			to_sleep(t_philo *philo);

//	CONTROL.C
void			wake_up_philos(t_philo *philos);

//	MAIN.C
pthread_mutex_t	*create_forks(t_requirement *req);
t_philo			*create_philos(t_requirement *req, pthread_mutex_t *forks);
t_requirement	parse_args(char argc, char *argv[]);

//	THREADS.C
suseconds_t		get_time(void);
void			ft_usleep(t_philo *philo, unsigned int n);
void			free_all(t_requirement *req, pthread_mutex_t *forks, \
					t_philo *philos);
void			free_forks(pthread_mutex_t *forks, int len);
void			show_action(t_philo *philo, char *msg);

//	UTILS.C
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_error(t_requirement *req, char *msg);
int				check_dead(t_philo *philo);

#endif
