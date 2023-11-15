/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/11/15 11:30:04 by oroy             ###   ########.fr       */
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

// Program status
# define DEATH -1
# define IDLE 0
# define START 1

// Fork status
# define OFF 0
# define ON 1

// Philo state
# define DEAD -1
# define THINKING 0
# define TAKING_FORKS 1
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
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				eat_max;
	int				program;
	int				philo_count;
	int				philo_full;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				state;
	pthread_t		th;
	t_env			*env;
	t_fork			*fork1;
	t_fork			*fork2;
	long int		start_time;
}	t_philo;

void		eating(t_philo *philo);
void		free_env(t_env *env);
void		*free_forks(t_fork **forks);
void		*free_philo(t_philo **philo);
void		free_philo_threads(t_philo **philo, int count);
void		free_structs(t_env *env, t_fork **forks, t_philo **philo);
int			ft_atoi(char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);
void		full(t_philo *philo);
long int	get_time(void);
t_env		*init_env(int argc, char **argv);
t_fork		**init_forks(int count);
t_philo		**init_philo(t_env *env, t_fork **forks);
void		main_thread(t_env *env, t_philo **philo);
bool		print_msg(t_philo *philo, int state, int macro);
void		program_kill(t_env *env);
void		program_pending(t_env *env);
void		program_start(t_env *env);
void		sleeping(t_philo *philo);
void		start_routine(t_env *env, t_philo **philo);
void		thinking(t_philo *philo);
void		usleep_iterate(long int usleep_total);
int			validate_args(int argc, char **argv);

#endif