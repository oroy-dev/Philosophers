/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:48:01 by oroy              #+#    #+#             */
/*   Updated: 2023/11/11 19:41:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is sleeping\n"))
		return ;
	if (!usleep_iterate(philo, philo->env->time_to_sleep))
		return ;
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is eating\n"))
		return ;
	if (!usleep_iterate(philo, philo->env->time_to_eat))
		return ;
	drop_fork(philo->fork1);
	drop_fork(philo->fork2);
	philo->fork_count = 0;
	philo->eat_count++;
	if (philo->eat_count == philo->env->eat_max)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
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
		else
			usleep_iterate(philo, 100);
		// check_death(philo);
	}
}
