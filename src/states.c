/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 20:29:31 by oroy             ###   ########.fr       */
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
	if (philo->env->eat_max != -1)
		philo->eat_count++;
	pthread_mutex_unlock (&philo->env->mutex_eat);
	usleep_iterate(philo->env->time_to_eat);
	drop_fork(philo->fork1);
	drop_fork(philo->fork2);
	philo->fork_count = 0;
	if (philo->eat_count == philo->env->eat_max)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	if (!print_msg(philo, THINKING))
		return ;
	while (philo->state == THINKING)
	{
		pthread_mutex_lock (&philo->env->mutex_print);
		if (philo->env->death == ON)
		{
			pthread_mutex_unlock (&philo->env->mutex_print);
			philo->state = DEAD;
			return ;
		}
		pthread_mutex_unlock (&philo->env->mutex_print);
		if (philo->fork_count == 0 && !pickup_fork(philo, philo->fork1))
			return ;
		if (philo->fork_count == 1 && !pickup_fork(philo, philo->fork2))
			return ;
		if (philo->fork_count == 2)
			philo->state = EATING;
	}
}
