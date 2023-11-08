/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/11/07 21:38:16 by olivierroy       ###   ########.fr       */
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

// Death Status
# define OFF 0
# define ON 1

// Fork Status
# define AVAILABLE 0
# define TAKEN 1

// Philo State
# define DEAD -1
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FULL 3

typedef struct s_forks
{
	int				status;
	pthread_mutex_t	mutex;
	struct s_forks	*next;
}	t_forks;

typedef struct s_env
{
	pthread_mutex_t	mutex;
	int				death;
	useconds_t		start_time;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	int				eat_times;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				fork_count;
	int				state;
	pthread_t		th;
	t_env			*env;
	t_forks			*fork1;
	t_forks			*fork2;
	useconds_t		start_time;
}	t_philo;

int	free_philo(t_philo *philo, int count);
int	ft_atoi(const char *str);
useconds_t	get_time(t_philo *philo);
int	print_msg(t_philo *philo, char *msg);
int	usleep_increment(t_philo *philo);
int	start_routine(t_philo **philo, int count);

#endif