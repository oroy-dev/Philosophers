/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:59:24 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 15:13:47 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

useconds_t	update_timestamp(t_philo *philo)
{
	static struct timeval	begin = {0, 0};
	struct timeval			now;
	useconds_t				time;

	if (begin.tv_sec == 0 && begin.tv_usec == 0)
		gettimeofday(&begin, NULL);
	gettimeofday(&now, NULL);
	time = (now.tv_sec - begin.tv_sec) * 1000000 + now.tv_usec - begin.tv_usec;
	philo->env->timestamp = time;
	return (philo->env->timestamp);
}

bool	usleep_iterate(t_philo *philo, useconds_t sleep_total)
{
	// useconds_t		sleep_iteration;
	useconds_t		start_time;
	struct timeval	time;

	// sleep_iteration = 100;
	gettimeofday(&time, NULL);
	start_time = time.tv_sec * 1000000 + time.tv_usec;
	while (update_timestamp(philo) - start_time < sleep_total)
	{
		usleep (100);
		philo->death_time = philo->env->timestamp - philo->start_time;
		// philo->death_time += sleep_iteration;
		if (philo->death_time >= philo->env->time_to_die)
		{
			print_death(philo);
			return (false);
		}
	}
	return (true);
}

// void	check_death(t_philo *philo)
// {
// 	if (philo->death_time >= philo->env->time_to_die)
// 		print_death(philo);
// }