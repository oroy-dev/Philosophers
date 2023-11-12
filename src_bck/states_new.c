/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/12 00:38:42 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	if (!print_msg(philo, SLEEPING))
		return ;
	usleep_iterate(philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	full(t_philo *philo)
{
	if (!print_msg(philo, FULL))
		return ;
	pthread_mutex_lock (&philo->env->mutex_eat);
	philo->env->philo_full++;
	pthread_mutex_unlock (&philo->env->mutex_eat);
}

void	eating(t_philo *philo)
{
	if (!print_msg(philo, EATING))
		return ;
	pthread_mutex_lock (&philo->env->mutex_eat);
	philo->start_time = get_time();
	pthread_mutex_unlock (&philo->env->mutex_eat);
	usleep_iterate(philo->env->time_to_eat);
	pthread_mutex_lock (&philo->fork1->mutex);
	philo->fork1->status = AVAILABLE;
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_lock (&philo->fork2->mutex);
	philo->fork2->status = AVAILABLE;
	pthread_mutex_unlock (&philo->fork2->mutex);
	philo->fork_count = 0;
	pthread_mutex_lock (&philo->env->mutex_eat);
	if (philo->env->eat_max != -1)
		philo->eat_count++;
	pthread_mutex_unlock (&philo->env->mutex_eat);
	if (philo->eat_count == philo->env->eat_max)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	if (!print_msg(philo, THINKING))
		return ;
	while (philo->fork_count < 2)
	{
		pthread_mutex_lock (&philo->fork1->mutex);
		if (philo->fork1->status == AVAILABLE)
		{
			if (!print_msg(philo, TAKEN_FORK))
			{
				pthread_mutex_unlock (&philo->fork1->mutex);
				if (philo->fork_count == 1)
				{
					pthread_mutex_lock (&philo->fork2->mutex);
					philo->fork2->status = AVAILABLE;
					pthread_mutex_unlock (&philo->fork2->mutex);
				}
				return ;
			}	
			philo->fork1->status = TAKEN;
			philo->fork_count++;
		}
		pthread_mutex_unlock (&philo->fork1->mutex);
		pthread_mutex_lock (&philo->fork2->mutex);
		if (philo->fork2->status == AVAILABLE)
		{
			if (!print_msg(philo, TAKEN_FORK))
			{
				pthread_mutex_unlock (&philo->fork2->mutex);
				if (philo->fork_count == 1)
				{
					pthread_mutex_lock (&philo->fork1->mutex);
					philo->fork1->status = AVAILABLE;
					pthread_mutex_unlock (&philo->fork1->mutex);
				}
				return ;
			}	
			philo->fork2->status = TAKEN;
			philo->fork_count++;
		}
		pthread_mutex_unlock (&philo->fork2->mutex);
		// usleep (100);
	}
	philo->state = EATING;
}
