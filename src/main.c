/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/10/20 14:43:50 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_rules(t_rules *rules, int argc, char **argv)
{
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->eat_times = ft_atoi(argv[5]);
	else
		rules->eat_times = -1;
}

static bool	init_philo(t_philo *philo, int count)
{
	t_philo	*current;
	t_philo	*tmp;
	int		i;

	if (count == 0)
		return (printf ("do something"));
	i = 0;
	tmp = NULL;
	while (i < count)
	{
		current = malloc (sizeof (t_philo));
		if (!current)
		{
			free_threads(philo, i);
			printf ("do something");
		}
		i++;
		current->id = i;
		current->fork_status = AVAILABLE;
		if (pthread_mutex_init (&current->fork, NULL) != 0)
			printf ("do something");
		if (tmp)
			tmp->next = current;
		else
			philo = current;
		tmp = current;
	}
	tmp->next = philo;
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_rules	rules;
	int		status;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required"));
	if (!init_philo(&philo, ft_atoi(argv[1])))
		return (printf ("Error: Failed to initialize philo threads"));
	init_rules(&rules, argc, argv);
	start_routine(&philo, ft_atoi(argv[1]));
	return (0);
}
