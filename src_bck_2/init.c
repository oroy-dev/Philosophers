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

t_philo	**init_philo(int count, t_fork *forks, t_env *env)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc (sizeof (t_philo *) * count);
	if (!philo)
		return (NULL);
	while (i < count)
	{
		philo[i] = malloc (sizeof (t_philo));
		if (!philo[i])
			printf ("Free philo array here\n");
		philo[i]->id = i + 1;
		philo[i]->eat_count = 0;
		philo[i]->fork_count = 0;
		if (i % 2 == 0)
		{
			philo[i]->fork1 = forks;
			philo[i]->fork2 = forks->next;
		}
		else
		{
			philo[i]->fork1 = forks->next;
			philo[i]->fork2 = forks;
		}
		philo[i]->state = THINKING;
		philo[i]->env = env;
		philo[i]->start_time = 0;
		philo[i]->death_time = 0;
		forks = forks->next;
		i++;
	}
	return (philo);
}

t_env	init_env(char **argv)
{
	t_env	env;

	if (pthread_mutex_init (&env.mutex, NULL) != 0)
		printf ("Do something here\n");
	env.death = OFF;
	env.timestamp = 0;
	env.time_to_die = ft_atoi(argv[2]) * 1000;
	env.time_to_eat = ft_atoi(argv[3]) * 1000;
	env.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		env.eat_max = ft_atoi(argv[5]);
	else
		env.eat_max = -1;
	return (env);
}

t_fork	*init_fork(int count, t_fork **forks)
{
	t_fork	*current;
	t_fork	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (i < count)
	{
		current = malloc (sizeof (t_fork));
		if (!current)
			printf ("Free forks list here\n");
		if (pthread_mutex_init (&current->mutex, NULL) != 0)
			printf ("Free forks list here\n");
		current->status = AVAILABLE;
		if (!tmp)
			*forks = current;
		else
			tmp->next = current;
		tmp = current;
		i++;
	}
	tmp->next = *forks;
	return (*forks);
}
