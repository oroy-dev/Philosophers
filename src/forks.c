/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:01:55 by oroy              #+#    #+#             */
/*   Updated: 2023/11/09 16:09:10 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock (&fork->mutex);
	fork->status = AVAILABLE;
	pthread_mutex_unlock (&fork->mutex);
}

bool	pickup_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock (&fork->mutex);
	if (fork->status == AVAILABLE)
	{
		if (!print_msg(philo, "%u %i has taken a fork\n"))
		{
			pthread_mutex_unlock (&fork->mutex);
			return (false);
		}
		fork->status = TAKEN;
		philo->fork_count++;
	}
	pthread_mutex_unlock (&fork->mutex);
	return (true);
}
