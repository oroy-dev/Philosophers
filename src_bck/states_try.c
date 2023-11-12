/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_try.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/11 19:41:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock (&philo->env->mutex);
	printf ("%ld %i is sleeping\n", get_time(), philo->id);
	pthread_mutex_unlock (&philo->env->mutex);
	usleep (philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock (&philo->env->mutex);
	printf ("%ld %i is eating\n", get_time(), philo->id);
	philo->start_time = get_time();
	pthread_mutex_unlock (&philo->env->mutex);
	usleep (philo->env->time_to_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	if (philo->env->eat_max != -1)
		philo->eat_count++;
	if (philo->eat_count == philo->env->eat_max)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock (&philo->env->mutex);
	printf ("%ld %i is thinking\n", get_time(), philo->id);
	pthread_mutex_unlock (&philo->env->mutex);
	pthread_mutex_lock (&philo->fork1->mutex);
	pthread_mutex_lock (&philo->fork2->mutex);
	philo->state = EATING;
}
