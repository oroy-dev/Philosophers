/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/31 15:23:01 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec / 1000);
}

void	sleeping(t_philo *philo)
{
	printf ("%i %i is sleeping\n", print_time(), philo->id);
	usleep(philo->rules->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	printf ("%i %i is eating\n", print_time(), philo->id);
	usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock (&philo->fork->mutex);
	pthread_mutex_unlock (&philo->fork->next->mutex);
	philo->state = SLEEPING;
}

void	thinking(t_philo *philo)
{
	printf ("%i %i is thinking\n", print_time(), philo->id);
	pthread_mutex_lock (&philo->fork->mutex);
	printf ("%i %i has taken a fork\n", print_time(), philo->id);
	pthread_mutex_lock (&philo->fork->next->mutex);
	printf ("%i %i has taken a fork\n", print_time(), philo->id);
	philo->state = EATING;
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	// countdown = philo->rules->time_to_die;
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
