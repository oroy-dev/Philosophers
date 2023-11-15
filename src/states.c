/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/15 11:16:16 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	if (!print_msg(philo, philo->state, SLEEPING))
		return ;
	usleep_iterate(philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	full(t_philo *philo)
{
	if (!print_msg(philo, philo->state, FULL))
		return ;
	pthread_mutex_lock (&philo->env->mutex_eat);
	philo->env->philo_full++;
	pthread_mutex_unlock (&philo->env->mutex_eat);
}

void	eating(t_philo *philo)
{
	if (!print_msg(philo, philo->state, EATING))
	{
		pthread_mutex_unlock (&philo->fork1->mutex);
		pthread_mutex_unlock (&philo->fork2->mutex);
		return ;
	}
	pthread_mutex_lock (&philo->env->mutex_eat);
	philo->start_time = get_time();
	pthread_mutex_unlock (&philo->env->mutex_eat);
	usleep_iterate(philo->env->time_to_eat);
	pthread_mutex_lock (&philo->env->mutex_eat);
	if (philo->env->eat_max != -1)
		philo->eat_count++;
	pthread_mutex_unlock (&philo->env->mutex_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	if (philo->eat_count == philo->env->eat_max)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	if (!print_msg(philo, philo->state, THINKING))
		return ;
	if (philo->state == THINKING)
	{
		philo->state = TAKING_FORKS;
		pthread_mutex_lock (&philo->fork1->mutex);
		if (!print_msg(philo, philo->state, TAKING_FORKS))
		{
			pthread_mutex_unlock (&philo->fork1->mutex);
			return ;
		}
	}
	if (philo->env->philo_count > 1)
	{
		pthread_mutex_lock (&philo->fork2->mutex);
		if (!print_msg(philo, philo->state, TAKING_FORKS))
		{
			pthread_mutex_unlock (&philo->fork1->mutex);
			pthread_mutex_unlock (&philo->fork2->mutex);
			return ;
		}
		philo->state = EATING;
	}
}
