/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/12 01:02:33 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep (50 * philo->env->philo_count);
	while (philo->state != DEAD && philo->state != FULL)
	{
		if (philo->state == THINKING)
			thinking(philo);
		if (philo->state == EATING)
			eating(philo);
		if (philo->state == SLEEPING)
			sleeping(philo);
		if (philo->state == FULL)
			full(philo);
	}
	return (NULL);
}

void	start_routine(t_env *env, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_create (&philo[i]->th, NULL, &routine, (void *)philo[i]))
			perror ("Error");
		i++;
	}
	while (true)
	{
		i = 0;
		while (i < env->philo_count)
		{
			pthread_mutex_lock (&env->mutex_eat);
			if (philo[i]->eat_count != env->eat_max
				&& get_time() - philo[i]->start_time >= env->time_to_die)
			{
				pthread_mutex_unlock (&env->mutex_eat);
				print_msg(philo[i], DEAD);
				free_philo(philo, env->philo_count);
				return ;
			}
			else if (env->philo_full >= env->philo_count)
			{
				pthread_mutex_unlock (&env->mutex_eat);
				free_philo(philo, env->philo_count);
				return ;
			}
			pthread_mutex_unlock (&env->mutex_eat);
			i++;
		}
	}
}
