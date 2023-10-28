/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/27 23:22:27 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo *philo)
{
	printf ("%i is sleeping\n", philo->id);
	usleep(philo->rules->time_to_sleep);
	printf ("%i is thinking\n", philo->id);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	printf ("%i is eating\n", philo->id);
	usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock (&philo->fork->mutex);
	pthread_mutex_unlock (&philo->fork->next->mutex);
	philo->fork->status = AVAILABLE;
	philo->fork->next->status = AVAILABLE;
	philo->fork_count = 0;
	philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	if (philo->fork->status == AVAILABLE && philo->fork->next->status == AVAILABLE)
	{
		philo->fork->status = TAKEN;
		philo->fork->next->status = TAKEN;
		pthread_mutex_lock (&philo->fork->mutex);
		pthread_mutex_lock (&philo->fork->next->mutex);
		printf ("%i has taken a fork\n", philo->id);
		printf ("%i has taken a fork\n", philo->id);
		philo->state = EATING;
	}
	// if (philo->fork_count == 2)
	// 	philo->state = EATING;
}

void	*routine(void *arg)
{
	// useconds_t	countdown;
	t_philo		*philo;

	philo = (t_philo *)arg;
	// countdown = philo->rules->time_to_die;
	printf ("%i is thinking\n", philo->id);
	while (philo->state != DEAD)
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

int	start_routine(t_philo **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create (&philo[i]->th, NULL, &routine, (void *)philo[i]))
			perror ("Error");
		i++;
	}
	return (0);
}
