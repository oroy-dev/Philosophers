/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/31 20:04:44 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

useconds_t	get_time(t_philo *philo)
{
	// static struct timeval	start = {0, 0};

	gettimeofday(philo->time, NULL);
	return ((philo->time->tv_usec * 1000000 + philo->time->tv_usec) - philo->start_time);
}

void	sleeping(t_philo *philo)
{
	printf ("%f %i is sleeping\n", get_time(philo) * 0.001, philo->id);
	usleep (philo->rules->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	printf ("%f %i is eating\n", get_time(philo) * 0.001, philo->id);
	usleep (philo->rules->time_to_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	philo->state = SLEEPING;
}

void	pickup_fork(t_philo *philo, t_forks *fork)
{
	pthread_mutex_lock (&fork->mutex);
	printf ("%f %i has taken a fork\n", get_time(philo) * 0.001, philo->id);
}

void	thinking(t_philo *philo)
{
	printf ("%f %i is thinking\n", get_time(philo) * 0.001, philo->id);
	pickup_fork(philo, philo->fork1);
	pickup_fork(philo, philo->fork2);
	philo->state = EATING;
}

void	*routine(void *arg)
{
	t_philo	*philo;

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

int	start_routine(t_philo **philo, int count, struct timeval *time)
{
	struct timeval	start;
	useconds_t		start_time;
	int				i;

	i = 0;
	gettimeofday(&start, NULL);
	start_time = start.tv_sec * 1000000 + start.tv_usec;
	while (i < count)
	{
		philo[i]->start_time = start_time;
		philo[i]->time = time;
		if (pthread_create (&philo[i]->th, NULL, &routine, (void *)philo[i]))
			perror ("Error");
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_join (philo[i]->th, NULL))
			perror ("Error");
		i++;
	}
	return (0);
}
