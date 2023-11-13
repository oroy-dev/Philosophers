/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 15:59:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_env	env;
	t_fork	**forks;
	t_philo	**philo;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	if (!check_args_valid(argc, argv))
		return (printf ("Error: Make sure to enter positive numbers only\n"));
	if (ft_atoi(argv[1]) < 1)
		return (printf ("Error: At least one philosopher required\n"));
	env = init_env(argv);
	forks = init_forks(env.philo_count);
	if (!forks)
		return (printf ("Error: Failed to initialize forks\n"));
	philo = init_philo(&env, forks);
	if (!philo)
		return (printf ("Error: Failed to initialize philosophers\n"));
	start_routine(&env, philo);
	free_philo(philo, env.philo_count);
	return (0);
}
