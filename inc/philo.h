/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/10/24 14:43:11 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

// Fork Status
# define AVAILABLE 0
# define TAKEN 1

// Philo Status
# define DEAD -1
# define THINKING 0
# define EATING 1
# define SLEEPING 2

typedef struct s_rules
{
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	useconds_t	eat_times;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				fork_count;
	int				fork_status;
	int				state;
	pthread_mutex_t	mutex;
	pthread_t		th;
	t_rules			rules;
	struct s_philo	*next;
}	t_philo;

int	free_philo(t_philo *philo, int count);
int	ft_atoi(const char *str);
int	start_routine(t_philo *philo, int count);

#endif