/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 19:14:22 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	print_msg("%ld %i is sleeping\n", philo);
	usleep (philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	print_msg("%ld %i is eating\n", philo);
	philo->start_time = get_time();
	usleep (philo->env->time_to_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	if (philo->env->eat_times != -1)
		philo->eat_count++;
	if (philo->eat_count == philo->env->eat_times)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	print_msg("%ld %i is thinking\n", philo);
	pthread_mutex_lock (&philo->fork1->mutex);
	pthread_mutex_lock (&philo->fork2->mutex);
	philo->state = EATING;
}
