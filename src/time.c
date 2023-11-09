/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:59:24 by oroy              #+#    #+#             */
/*   Updated: 2023/11/09 17:14:40 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

useconds_t	update_timestamp(t_philo *philo)
{
	struct timeval	current;
	useconds_t		time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000000 + current.tv_usec - philo->env->start_time;
	philo->env->timestamp = time;
	return (philo->env->timestamp);
}

bool	usleep_iterate(t_philo *philo, useconds_t sleep_total)
{
	useconds_t	sleep_iteration;
	useconds_t	timer;

	sleep_iteration = 100;
	timer = 0;
	while (timer < sleep_total)
	{
		usleep (sleep_iteration);
		philo->death_time = update_timestamp(philo) - philo->start_time;
		if (philo->death_time >= philo->env->time_to_die)
		{
			print_death(philo);
			return (false);
		}
		timer += sleep_iteration;
	}
	return (true);
}

// void	check_death(t_philo *philo)
// {
// 	if (philo->death_time >= philo->env->time_to_die)
// 		print_death(philo);
// }