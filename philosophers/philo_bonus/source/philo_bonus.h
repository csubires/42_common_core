/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:57 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <memory.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "/forks"
# define SEM_SHOW "/show"

# define TO_MICROSEG 1000

# define ERR_ARGS "Invalid arguments."
# define ERR_ZERO "nbr_of_philosophers and num_must_eat must be greater than 0"
# define ERR_THREAD "Failed to create a thread"
# define ERR_JOIN "Failed to join a thread"
# define ERR_FORK "Failed to create a fork"
# define ERR_WAIT "Failed to wait a children"
# define ERR_MALLOC "Failed to allocate memory"
# define ERR_SEM "Failed to initialize semaphore"
# define MSG_HELP "\033[38;5;208mUse:\033[0m ./philo \33[93mnumber_of_philosophers \
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
	int					one_error;
	sem_t				*sem_forks;
	sem_t				*sem_show;
}	t_requirement;

typedef struct s_philo
{
	pid_t				t_pid;
	int					index_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	int					i_live;
	int					eating;
	suseconds_t			start_time;
	suseconds_t			last_time_ate;
	pthread_t			dead_pid;
	t_requirement		*req;
}	t_philo;

//	ACTIONS_BONUS.C
int				am_i_dead(t_philo *philo);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			to_eat(t_philo *philo);
void			to_sleep(t_philo *philo);

//	CONTROL_BONUS.C
void			*check_dead(void *params);
void			tasks_philo(t_philo *philo);
void			wake_up_philos(t_requirement *req, t_philo *philos);
void			wait_children(t_philo *philos);

//	MAIN.C
t_philo			*create_philos(t_requirement *req);
t_requirement	parse_args(char argc, char *argv[]);
int				check_args(int argc, char *argv[]);

//	PROCESS_BONUS
suseconds_t		get_time(void);
void			ft_usleep(t_philo *philo, unsigned int n);
int				activate_sems(t_requirement *req);
void			print_goal(t_requirement *req, int goal);
void			show_action(t_philo *philo, char *msg);

//	UTILS_BONUS.C
int				ft_isspace(char c);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			free_all(t_requirement *req, t_philo *philos);
int				ft_error(t_requirement *req, char *msg);

#endif
