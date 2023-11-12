/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:10:31 by oroy              #+#    #+#             */
/*   Updated: 2023/11/12 00:49:17 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static char	*get_msg(int state)
{
	if (state == DEAD)
		return ("%ld %i died\n");
	if (state == THINKING)
		return ("%ld %i is thinking\n");
	if (state == TAKEN_FORK)
		return ("%ld %i has taken a fork\n");
	if (state == EATING)
		return ("%ld %i is eating\n");
	if (state == SLEEPING)
		return ("%ld %i is sleeping\n");
	return ("%ld %i has eaten plentifully\n");
}

bool	print_msg(t_philo *philo, int state)
{
	pthread_mutex_lock (&philo->env->mutex_print);
	if (philo->env->death == ON)
	{
		philo->state = DEAD;
		pthread_mutex_unlock (&philo->env->mutex_print);
		return (false);
	}
	printf (get_msg(state), get_time(), philo->id);
	if (state == DEAD)
		philo->env->death = ON;
	pthread_mutex_unlock (&philo->env->mutex_print);
	return (true);
}
