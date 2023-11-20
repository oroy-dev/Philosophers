/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:42:44 by oroy              #+#    #+#             */
/*   Updated: 2023/11/20 15:54:54 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_env(t_env *env)
{
	pthread_mutex_destroy (&env->mutex_eat);
	pthread_mutex_destroy (&env->mutex_print);
	ft_free(env);
}

void	*free_forks(t_fork **forks)
{
	int	i;

	i = 0;
	while (forks[i])
	{
		if (forks[i]->status == ON)
			pthread_mutex_destroy (&forks[i]->mutex);
		ft_free(forks[i]);
		i++;
	}
	return (ft_free(forks));
}

void	*free_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		ft_free(philo[i]);
		i++;
	}
	return (ft_free(philo));
}

void	free_philo_threads(t_philo **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join (philo[i]->th, NULL);
		i++;
	}
}

void	free_structs(t_env *env, t_fork **forks, t_philo **philo)
{
	if (env)
		free_env(env);
	if (forks)
		free_forks(forks);
	if (philo)
		free_philo(philo);
}
