/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/10/18 16:06:38 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	init_philo(t_philo *philo, int argc, char **argv)
{
	philo->threads = malloc (sizeof (pthread_t) * ft_atoi(argv[1]));
	if (!philo->threads)
		return (false);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_times = ft_atoi(argv[5]);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required"));
	if (!init_philo(&philo, argc, argv))
		return (printf ("Error: Failed to initialize philo threads"));
	start_routine(&philo, ft_atoi(argv[1]));
	return (0);
}
