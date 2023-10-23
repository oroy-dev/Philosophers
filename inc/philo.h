/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/10/23 19:12:51 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

# define AVAILABLE 0
# define TAKEN 1

typedef struct s_rules
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_times;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				fork_status;
	pthread_mutex_t	fork;
	pthread_t		th;
	struct s_philo	*next;
}	t_philo;

int	free_philo(t_philo *philo, int count);
int	ft_atoi(const char *str);
int	start_routine(t_philo *philo, int count, t_rules *rules);

#endif