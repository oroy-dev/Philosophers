/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 15:39:33 by oroy             ###   ########.fr       */
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
# define TAKEN_FORK 1
# define EATING 2
# define SLEEPING 3
# define FULL 4

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				status;
}	t_fork;

typedef struct s_env
{
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_print;
	long int		timestamp;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				eat_max;
	int				death;
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
void		full(t_philo *philo);
long int	get_time(void);
t_env		init_env(char **argv);
t_fork		**init_forks(int count);
t_philo		**init_philo(t_env *env, t_fork **forks);
void		main_thread(t_env *env, t_philo **philo);
bool		pickup_fork(t_philo *philo, t_fork *fork);
void		print_death(t_philo *philo);
bool		print_msg(t_philo *philo, int state);
void		sleeping(t_philo *philo);
void		start_routine(t_env *env, t_philo **philo);
void		thinking(t_philo *philo);
void		usleep_iterate(long int usleep_total);

#endif