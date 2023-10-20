/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/10/20 14:31:46 by olivierroy       ###   ########.fr       */
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
	t_philo			*next;
}	t_philo;

void	free_philo(t_philo *philo, int count);
int		ft_atoi(const char *str);
int		start_routine(t_philo *philo, int thread_count);

#endif