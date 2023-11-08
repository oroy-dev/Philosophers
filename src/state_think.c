/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:48:01 by oroy              #+#    #+#             */
/*   Updated: 2023/11/08 17:07:48 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	pickup_fork(t_philo *philo, t_forks *fork)
{
	pthread_mutex_lock (&fork->mutex);
	if (fork->status == AVAILABLE)
	{
		if (!print_msg(philo, "%u %i has taken a fork\n"))
		{
			pthread_mutex_unlock (&fork->mutex);
			return (0);
		}
		fork->status = TAKEN;
		philo->fork_count++;
	}
	pthread_mutex_unlock (&fork->mutex);
	return (1);
}

void	thinking(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is thinking\n"))
		return ;
	while (philo->state == THINKING)
	{
		if (philo->fork_count == 0)
		{
			if (!pickup_fork(philo, philo->fork1))
				return ;
		}
		if (philo->fork_count == 1)
		{
			if (!pickup_fork(philo, philo->fork2))
			{
				pthread_mutex_lock (&philo->fork1->mutex);
				philo->fork1->status = AVAILABLE;
				pthread_mutex_unlock (&philo->fork1->mutex);
				return ;
			}
		}
		if (philo->fork_count == 2)
			philo->state = EATING;
		check_time(philo);
	}
}
