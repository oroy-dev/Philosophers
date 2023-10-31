/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/10/31 15:09:51 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo	**init_philo(int count, t_forks *forks, t_rules *rules)
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
		philo[i]->fork_count = 0;
		philo[i]->fork = forks;
		philo[i]->state = THINKING;
		philo[i]->rules = rules;
		forks = forks->next;
		i++;
	}
	return (philo);
}

static t_rules	init_rules(char **argv)
{
	t_rules	rules;

	rules.time_to_die = ft_atoi(argv[2]) * 1000;
	rules.time_to_eat = ft_atoi(argv[3]) * 1000;
	rules.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		rules.eat_times = ft_atoi(argv[5]);
	else
		rules.eat_times = -1;
	return (rules);
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

int	main(int argc, char **argv)
{
	int				count;
	t_forks			*forks;
	t_philo			**philo;
	t_rules			rules;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	count = ft_atoi(argv[1]);
	if (count <= 0)
		return (printf ("Error: At least 1 philosopher required\n"));
	forks = init_forks(count, &forks);
	if (!forks)
		return (printf ("Error: Failed to initialize forks\n"));
	rules = init_rules(argv);
	philo = init_philo(count, forks, &rules);
	if (!philo)
		return (printf ("Error: Failed to initialize philosophers\n"));
	start_routine(philo, count);
	return (0);
}
