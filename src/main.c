/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 20:01:00 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_env	*env;
	t_fork	**forks;
	t_philo	**philo;

	if (validate_args(argc, argv))
		return (1);
	env = init_env(argc, argv);
	if (!env)
		return (printf ("Error: Failed to initialize env\n"));
	forks = init_forks(env->philo_count);
	if (!forks)
		return (printf ("Error: Failed to initialize forks\n"));
	philo = init_philo(env, forks);
	if (!philo)
		return (printf ("Error: Failed to initialize philo\n"));
	start_routine(env, philo);
	free_all(philo, env->philo_count);
	return (0);
}
