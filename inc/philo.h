/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 18:45:32 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// Death status
# define OFF 0
# define ON 1

// Fork status
# define AVAILABLE 0
# define TAKEN 1

// Philo state
# define DEAD -1
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FULL 3

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				status;
}	t_fork;

typedef struct s_env
{
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_print;
	useconds_t		timestamp;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	int				eat_times;
	int				philo_count;
	int				philo_full;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				fork_count;
	int				state;
	pthread_t		th;
	t_env			*env;
	t_fork			*fork1;
	t_fork			*fork2;
	long int		start_time;
}	t_philo;

bool		check_args_valid(int argc, char **argv);
void		check_death(t_philo *philo);
void		drop_fork(t_fork *fork);
void		eating(t_philo *philo);
void		free_philo(t_philo **philo, int philo_count);
int			ft_atoi(char *str);
long int	get_time(void);
t_env		init_env(char **argv);
t_fork		**init_forks(int count);
t_philo		**init_philo(t_env *env, t_fork **forks);
bool		pickup_fork(t_philo *philo, t_fork *fork);
void		print_death(t_philo *philo);
void		print_msg(char *msg, t_philo *philo);
void		sleeping(t_philo *philo);
void		start_routine(t_env *env, t_philo **philo);
void		thinking(t_philo *philo);
bool		usleep_iterate(t_philo *philo, useconds_t sleep_total);

#endif