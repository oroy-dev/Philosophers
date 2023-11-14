/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/14 17:18:19 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	program_pending(philo->env);
	if (philo->env->program == DEATH)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep (50 * philo->env->philo_count);
	while (philo->state != DEAD && philo->state != FULL)
	{
		if (philo->state == THINKING || philo->state == TAKING_FORKS)
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
		{
			printf ("Error: Failed to create philo threads\n");
			program_kill(env);
			free_philo_threads(philo, i);
			return ;
		}
		i++;
	}
	program_start(env);
	main_thread(env, philo);
}
