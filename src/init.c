/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:49:10 by oroy              #+#    #+#             */
/*   Updated: 2023/11/17 14:19:26 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	**init_philo(t_env *env, t_fork **forks)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = ft_calloc((env->philo_count + 1), sizeof (t_philo *));
	if (!philo)
		return (NULL);
	while (i < env->philo_count)
	{
		philo[i] = ft_calloc(1, sizeof (t_philo));
		if (!philo[i])
			return (free_philo(philo));
		philo[i]->id = i + 1;
		philo[i]->eat_count = 0;
		philo[i]->env = env;
		philo[i]->state = THINKING;
		philo[i]->start_time = 0;
		philo[i]->fork1 = forks[philo[i]->id - 1];
		philo[i]->fork2 = forks[philo[i]->id % env->philo_count];
		i++;
	}
	philo[i] = NULL;
	return (philo);
}

t_fork	**init_forks(int count)
{
	t_fork	**forks;
	int		i;

	i = 0;
	forks = ft_calloc((count + 1), sizeof (t_fork *));
	if (!forks)
		return (NULL);
	while (i < count)
	{
		forks[i] = ft_calloc(1, sizeof (t_fork));
		if (!forks[i])
			return (free_forks(forks));
		if (pthread_mutex_init (&forks[i]->mutex, NULL))
			return (free_forks(forks));
		forks[i]->status = ON;
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

t_env	*init_env(int argc, char **argv)
{
	t_env	*env;

	env = ft_calloc(1, sizeof (t_env));
	if (!env)
		return (NULL);
	if (pthread_mutex_init (&env->mutex_eat, NULL))
		return (ft_free(env));
	if (pthread_mutex_init (&env->mutex_print, NULL))
	{
		pthread_mutex_destroy (&env->mutex_eat);
		return (ft_free(env));
	}
	env->philo_count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_max = ft_atoi(argv[5]);
	else
		env->eat_max = -1;
	env->philo_full = 0;
	env->program = IDLE;
	return (env);
}
