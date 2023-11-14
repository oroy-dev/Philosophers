/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:07:19 by oroy              #+#    #+#             */
/*   Updated: 2023/11/14 17:18:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	program_pending(t_env *env)
{
	while (true)
	{
		pthread_mutex_lock (&env->mutex_print);
		if (env->program != IDLE)
			break ;
		pthread_mutex_unlock (&env->mutex_print);
	}
	pthread_mutex_unlock (&env->mutex_print);
}

void	program_kill(t_env *env)
{
	pthread_mutex_lock (&env->mutex_print);
	env->program = DEATH;
	pthread_mutex_unlock (&env->mutex_print);
}

void	program_start(t_env *env)
{
	pthread_mutex_lock (&env->mutex_print);
	env->program = START;
	pthread_mutex_unlock (&env->mutex_print);
}
