/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:04:41 by olivierroy        #+#    #+#             */
/*   Updated: 2023/11/07 21:32:33 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	usleep_increment(t_philo *philo)
{
	useconds_t	sleep_time;
	useconds_t	elapsed;
	useconds_t	timer;

	sleep_time = 10000;
	elapsed = 0;
	timer = 0;
	while (timer < philo->env->time_to_sleep)
	{
		usleep (sleep_time);
		elapsed = get_time(philo) - philo->start_time;
		if (elapsed >= philo->env->time_to_die)
		{
			print_msg(philo, "%u %i died\n");
			return (0);
		}
		timer += sleep_time;
	}
	return (1);
}
