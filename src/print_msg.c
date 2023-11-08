/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:54:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/08 16:55:11 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_msg(t_philo *philo, char *msg)
{
	useconds_t	current;
	
	pthread_mutex_lock (&philo->env->mutex);
	if (philo->env->death == OFF)
	{
		current = get_time(philo);
		if (philo->state == EATING)
			philo->start_time = current;
		// printf ("Philo Timer: %u\n", current - philo->start_time);
		if (current - philo->start_time < philo->env->time_to_die)
		{
			printf (msg, current, philo->id);
			pthread_mutex_unlock (&philo->env->mutex);
			return (1);
		}
		else
		{
			// printf ("Philo Timer: %u\n", current - philo->start_time);
			printf ("%u %i died\n", current, philo->id);
			philo->env->death = ON;
		}
	}
	philo->state = DEAD;
	pthread_mutex_unlock (&philo->env->mutex);
	return (0);
}
