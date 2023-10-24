/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/10/24 18:49:44 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	init_philo(t_philo **philo, int count, t_rules rules)
{
	t_philo	*current;
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (i < count)
	{
		current = malloc (sizeof (t_philo));
		if (!current)
			return (free_philo(*philo, i));
		i++;
		if (pthread_mutex_init (&current->mutex, NULL) != 0)
			return (free_philo(*philo, i));
		current->id = i;
		current->fork_count = 0;
		current->fork_status = AVAILABLE;
		current->state = THINKING;
		current->rules = rules;
		if (tmp)
			tmp->next = current;
		else
			*philo = current;
		tmp = current;
	}
	tmp->next = *philo;
	return (true);
}

static void	init_rules(t_rules *rules, char **argv)
{
	rules->time_to_die = ft_atoi(argv[2]) * 1000;
	rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		rules->eat_times = ft_atoi(argv[5]);
	else
		rules->eat_times = -1;
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;
	int		count;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	count = ft_atoi(argv[1]);
	if (count <= 0)
		return (printf ("Error: At least 1 philosopher required\n"));
	init_rules(&rules, argv);
	if (!init_philo(&philo, count, rules))
		return (printf ("Error: Failed to initialize philosophers\n"));
	start_routine(philo, count);
	return (0);
}