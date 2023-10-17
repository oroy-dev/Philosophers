/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/10/16 22:06:45 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*init_philo(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc (sizeof (t_philo));
	if (!philo)
		return (NULL);
	philo->threads = malloc (sizeof (pthread_t) * ft_atoi(argv[1]));
	if (!philo->threads)
	{
		ft_free(philo);
		return (NULL);
	}
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_times = ft_atoi(argv[5]);
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	
	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required"));
	philo = init_philo(argc, argv);
	if (!philo)
		return (printf ("Error: Failed to create philo threads"));
	return (0);
}
