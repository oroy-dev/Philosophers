/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:49:10 by oroy              #+#    #+#             */
/*   Updated: 2023/11/11 19:41:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	assign_forks(t_philo *philo, t_fork **forks)
{
	if (philo->id % 2 == 1)
	{
		philo->fork1 = forks[philo->id - 1];
		philo->fork2 = forks[philo->id % philo->env->philo_count];
	}
	else
	{
		philo->fork1 = forks[philo->id % philo->env->philo_count];
		philo->fork2 = forks[philo->id - 1];
	}
}

t_philo	**init_philo(t_env *env, t_fork **forks)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc (sizeof (t_philo *) * env->philo_count);
	if (!philo)
		return (NULL);
	while (i < env->philo_count)
	{
		philo[i] = malloc (sizeof (t_philo));
		if (!philo[i])
			printf ("Free philo array here\n");
		philo[i]->id = i + 1;
		philo[i]->eat_count = 0;
		philo[i]->fork_count = 0;
		philo[i]->env = env;
		philo[i]->state = THINKING;
		philo[i]->start_time = 0;
		assign_forks(philo[i], forks);
		i++;
	}
	return (philo);
}

t_fork	**init_forks(int count)
{
	t_fork	**forks;
	t_fork	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	forks = malloc (sizeof (t_fork *) * count);
	if (!forks)
		return (NULL);
	while (i < count)
	{
		forks[i] = malloc (sizeof (t_fork));
		if (!forks[i])
			printf ("Free forks array here\n");
		if (pthread_mutex_init (&forks[i]->mutex, NULL) != 0)
			printf ("Free forks array here\n");
		forks[i]->status = AVAILABLE;
		i++;
	}
	return (forks);
}

t_env	init_env(char **argv)
{
	t_env	env;

	if (pthread_mutex_init (&env.mutex_eat, NULL) != 0)
		printf ("Do something here\n");
	if (pthread_mutex_init (&env.mutex_print, NULL) != 0)
		printf ("Do something here\n");
	env.timestamp = 0;
	env.philo_count = ft_atoi(argv[1]);
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]) * 1000;
	env.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		env.eat_max = ft_atoi(argv[5]);
	else
		env.eat_max = -1;
	env.philo_full = 0;
	env.death = OFF;
	return (env);
}
