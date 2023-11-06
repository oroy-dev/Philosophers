/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/06 15:16:39 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

useconds_t	get_time(t_philo *philo)
{
	struct timeval	current;
	useconds_t		time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000000 + current.tv_usec - philo->env->start_time;
	return (time * 0.001);
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock (&philo->env->mutex);
	printf (msg, get_time(philo), philo->id);
	pthread_mutex_unlock (&philo->env->mutex);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, "%u %i is sleeping\n");
	usleep (philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	print_msg(philo, "%u %i is eating\n");
	usleep (philo->env->time_to_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	philo->eat_count++;
	if (philo->eat_count == philo->env->eat_times)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

void	pickup_fork(t_philo *philo, t_forks *fork)
{
	pthread_mutex_lock (&fork->mutex);
	print_msg(philo, "%u %i has taken a fork\n");
}

void	thinking(t_philo *philo)
{
	print_msg(philo, "%u %i is thinking\n");
	pickup_fork(philo, philo->fork1);
	pickup_fork(philo, philo->fork2);
	philo->state = EATING;
}

bool	still_hungry(t_philo *philo)
{
	if (philo->state == FULL)
	{
		print_msg(philo, "%u %i has eaten plentifully\n");
		return (false);
	}
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->state != DEAD	&& still_hungry(philo))
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
	i = 0;
	while (i < count)
	{
		if (pthread_join (philo[i]->th, NULL))
			perror ("Error");
		i++;
	}
	return (0);
}
