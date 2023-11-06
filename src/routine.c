/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/11/06 18:02:04 by oroy             ###   ########.fr       */
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

int	print_msg(t_philo *philo, char *msg)
{
	useconds_t	current;
	
	pthread_mutex_lock (&philo->env->mutex);
	if (philo->env->death == OFF)
	{
		current = get_time(philo);
		if (philo->state == EATING)
			philo->start_time = current;
		printf ("Philo Timer: %u\n", current - philo->start_time);
		if (current - philo->start_time < philo->env->time_to_die)
		{
			printf (msg, current, philo->id);
			pthread_mutex_unlock (&philo->env->mutex);
			return (1);
		}
		else
		{
			printf ("%u %i died\n", current, philo->id);
			philo->env->death = ON;
		}
	}
	philo->state = KILLED;
	pthread_mutex_unlock (&philo->env->mutex);
	return (0);
}

void	sleeping(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is sleeping\n"))
		return ;
	usleep (philo->env->time_to_sleep);
	philo->state = THINKING;
}

void	eating(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is eating\n"))
	{
		pthread_mutex_unlock (&philo->fork1->mutex);
		pthread_mutex_unlock (&philo->fork2->mutex);
		return ;
	}
	usleep (philo->env->time_to_eat);
	pthread_mutex_unlock (&philo->fork1->mutex);
	pthread_mutex_unlock (&philo->fork2->mutex);
	philo->eat_count++;
	if (philo->eat_count == philo->env->eat_times)
		philo->state = FULL;
	else
		philo->state = SLEEPING;
}

int	pickup_fork(t_philo *philo, t_forks *fork)
{
	pthread_mutex_lock (&fork->mutex);
	if (!print_msg(philo, "%u %i has taken a fork\n"))
		return (0);
	return (1);
}

void	thinking(t_philo *philo)
{
	if (!print_msg(philo, "%u %i is thinking\n"))
		return ;
	if (!pickup_fork(philo, philo->fork1))
	{
		pthread_mutex_unlock (&philo->fork1->mutex);
		return ;
	}
	if (!pickup_fork(philo, philo->fork2))
	{
		pthread_mutex_unlock (&philo->fork1->mutex);
		pthread_mutex_unlock (&philo->fork2->mutex);
		return ;
	}
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
	while (still_hungry(philo) && philo->state != KILLED)
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
