/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 19:14:58 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->state == THINKING)
			thinking(philo);
		if (philo->state == EATING)
			eating(philo);
		if (philo->state == SLEEPING)
			sleeping(philo);
		if (philo->state == FULL)
		{
			print_msg("%ld %i has eaten plentifully\n", philo);
			pthread_mutex_lock (&philo->env->mutex_eat);
			philo->env->philo_full++;
			pthread_mutex_unlock (&philo->env->mutex_eat);
			break ;
		}
	}
	return (NULL);
}

void	start_routine(t_env *env, t_philo **philo)
{
	bool	loop;
	int		i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_create (&philo[i]->th, NULL, &routine, (void *)philo[i]))
			perror ("Error");
		i++;
	}
	loop = true;
	while (loop)
	{
		// pthread_mutex_lock (&env->mutex_eat);
		// if (env->philo_full >= env->philo_count)
		// {
		// 	pthread_mutex_unlock (&env->mutex_eat);
		// 	free_philo(philo, env->philo_count);
		// 	break ;
		// }
		// pthread_mutex_unlock (&env->mutex_eat);
		i = 0;
		while (i < env->philo_count)
		{
			if (get_time() - philo[i]->start_time >= env->time_to_die)
			{
				print_msg("%ld %i died\n", philo[i]);
				free_philo(philo, env->philo_count);
				loop = false;
				break ;
			}
			i++;
		}
	}
}
