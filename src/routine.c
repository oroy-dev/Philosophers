/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/25 16:27:43 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	printf ("%i is sleeping\n", philo->id);
	usleep(philo->rules.time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	printf ("%i is eating\n", philo->id);
	usleep(philo->rules.time_to_eat);
	pthread_mutex_unlock (&philo->mutex);
	philo->fork_status = AVAILABLE;
	pthread_mutex_unlock (&philo->next->mutex);
	philo->next->fork_status = AVAILABLE;
	philo->fork_count = 0;
	philo->state = SLEEPING;
}

void	pickup_forks(t_philo *philo)
{
	if (philo->fork_status == AVAILABLE)
	{
		pthread_mutex_lock (&philo->mutex);
		printf ("%i has taken a fork\n", philo->id);
		philo->fork_status = TAKEN;
		philo->fork_count++;
	}
	if (philo->fork_status == TAKEN && philo->next->fork_status == AVAILABLE)
	{
		pthread_mutex_lock (&philo->next->mutex);
		printf ("%i has taken a fork\n", philo->id);
		philo->next->fork_status = TAKEN;
		philo->fork_count++;
	}
}

void	thinking(t_philo *philo)
{
	printf ("%i is thinking\n", philo->id);
	pickup_forks(philo);
	if (philo->fork_count == 2)
		philo->state = EATING;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (philo->state == THINKING)
			thinking(philo);
		if (philo->state == EATING)
			eating(philo);
		if (philo->state == SLEEPING)
			sleeping(philo);
	}
	return (NULL);
}

int	start_routine(t_env *env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create (env->philo[i]->th, NULL, &routine, (void *)env))
			perror ("Error");
		i++;
	}
	return (0);
}
