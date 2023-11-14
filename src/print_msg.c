/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:10:31 by oroy              #+#    #+#             */
/*   Updated: 2023/11/14 17:11:07 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static char	*get_msg(int state)
{
	if (state == DEAD)
		return ("%ld %i died\n");
	if (state == THINKING)
		return ("%ld %i is thinking\n");
	if (state == TAKING_FORKS)
		return ("%ld %i has taken a fork\n");
	if (state == EATING)
		return ("%ld %i is eating\n");
	if (state == SLEEPING)
		return ("%ld %i is sleeping\n");
	return ("%ld %i has eaten plentifully\n");
}

bool	print_msg(t_philo *philo, int state, int macro)
{
	pthread_mutex_lock (&philo->env->mutex_print);
	if (philo->env->program == DEATH)
	{
		philo->state = DEAD;
		pthread_mutex_unlock (&philo->env->mutex_print);
		return (false);
	}
	if (state == macro)
	{
		printf (get_msg(state), get_time(), philo->id);
		if (macro == DEAD)
			philo->env->program = DEATH;
	}
	pthread_mutex_unlock (&philo->env->mutex_print);
	return (true);
}
