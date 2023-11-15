/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:08:00 by oroy              #+#    #+#             */
/*   Updated: 2023/11/15 10:53:42 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	main_thread(t_env *env, t_philo **philo)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < env->philo_count)
		{
			pthread_mutex_lock (&env->mutex_eat);
			if (philo[i]->eat_count != env->eat_max
				&& get_time() - philo[i]->start_time >= env->time_to_die)
			{
				pthread_mutex_unlock (&env->mutex_eat);
				print_msg(philo[i], DEAD, DEAD);
				return ;
			}
			else if (env->philo_full >= env->philo_count)
			{
				pthread_mutex_unlock (&env->mutex_eat);
				return ;
			}
			pthread_mutex_unlock (&env->mutex_eat);
			i++;
		}
	}
}
