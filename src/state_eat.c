/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:06:07 by oroy              #+#    #+#             */
/*   Updated: 2023/11/08 17:08:25 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is eating\n"))
		return ;
	usleep (philo->env->time_to_eat);
	philo->start_time = get_time(philo);
	pthread_mutex_lock (&philo->fork1->mutex);
	philo->fork1->status = AVAILABLE;
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_lock (&philo->fork2->mutex);
	philo->fork2->status = AVAILABLE;
	pthread_mutex_unlock (&philo->fork2->mutex);
	philo->fork_count = 0;
	philo->eat_count++;
	if (philo->eat_count == philo->env->eat_times)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}
