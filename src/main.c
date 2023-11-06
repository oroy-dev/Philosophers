/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/06 16:34:14 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo	**init_philo(int count, t_forks *forks, t_env *env)
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
		forks = forks->next;
		i++;
	}
	return (philo);
}

static t_env	init_env(char **argv)
{
	struct timeval	time;
	t_env			env;

	if (pthread_mutex_init (&env.mutex, NULL) != 0)
		printf ("Do something here\n");
	gettimeofday(&time, NULL);
	env.death = OFF;
	env.start_time = time.tv_sec * 1000000 + time.tv_usec;
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]) * 1000;
	env.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		env.eat_times = ft_atoi(argv[5]);
	else
		env.eat_times = -1;
	return (env);
}

static t_forks	*init_forks(int count, t_forks **forks)
{
	t_forks	*current;
	t_forks	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (i < count)
	{
		current = malloc (sizeof (t_forks));
		if (!current)
			printf ("Free forks list here\n");
		if (pthread_mutex_init (&current->mutex, NULL) != 0)
			printf ("Free forks list here\n");
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

int	main(int argc, char **argv)
{
	int				count;
	t_env			env;
	t_forks			*forks;
	t_philo			**philo;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	count = ft_atoi(argv[1]);
	if (count <= 0)
		return (printf ("Error: At least 1 philosopher required\n"));
	forks = init_forks(count, &forks);
	if (!forks)
		return (printf ("Error: Failed to initialize forks\n"));
	env = init_env(argv);
	philo = init_philo(count, forks, &env);
	if (!philo)
		return (printf ("Error: Failed to initialize philosophers\n"));
	start_routine(philo, count);
	return (0);
}
