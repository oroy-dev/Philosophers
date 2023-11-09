/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:54:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/09 17:09:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_death(t_philo *philo)
{
	pthread_mutex_lock (&philo->env->mutex);
	if (philo->env->death == OFF)
	{
		update_timestamp(philo);
		printf ("%u %i died\n", philo->env->timestamp / 1000, philo->id);
		philo->env->death = ON;
	}
	philo->state = DEAD;
	pthread_mutex_unlock (&philo->env->mutex);
}

bool	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock (&philo->env->mutex);
	if (philo->env->death == OFF)
	{
		update_timestamp(philo);
		if (philo->state == EATING)
			philo->start_time = philo->env->timestamp;
		philo->death_time = philo->env->timestamp - philo->start_time;
		if (philo->death_time < philo->env->time_to_die)
		{
			printf (msg, philo->env->timestamp / 1000, philo->id);
			pthread_mutex_unlock (&philo->env->mutex);
			return (true);
		}
		else
		{
			printf ("%u %i died\n", philo->env->timestamp / 1000, philo->id);
			philo->env->death = ON;
		}
	}
	philo->state = DEAD;
	pthread_mutex_unlock (&philo->env->mutex);
	return (false);
}
