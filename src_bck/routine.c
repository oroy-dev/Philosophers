/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/11 19:28:51 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->state != DEAD)
	{
		thinking(philo);
		eating(philo);
		eating_full(philo);
		sleeping(philo);
		if (philo->state == FULL)
		{
			if (!print_msg(philo, FULL))
				break ;
			pthread_mutex_lock (&philo->env->mutex_eat);
			philo->env->philo_count--;
			pthread_mutex_unlock (&philo->env->mutex_eat);
			break ;
		}
	}
	return (NULL);
}

void	start_routine(t_env *env, t_philo **philo)
{
	int		i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_create (&philo[i]->th, NULL, &routine, (void *)philo[i]))
			perror ("Error");
		// if (pthread_detach (philo[i]->th))
		// 	perror ("Error");
		i++;
	}
	while (env->philo_count)
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
			pthread_mutex_lock (&env->mutex_eat);
			if (get_time() - philo[i]->start_time >= env->time_to_die)
			{
				pthread_mutex_unlock (&env->mutex_eat);
				print_msg(philo[i], DEAD);
				free_philo(philo, env->philo_count);
				return ;
			}
			pthread_mutex_unlock (&env->mutex_eat);
			i++;
		}
	}
}
