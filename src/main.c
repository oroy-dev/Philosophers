/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:35:49 by oroy              #+#    #+#             */
/*   Updated: 2023/11/09 16:05:04 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	int				count;
	t_env			env;
	t_fork			*forks;
	t_philo			**philo;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	if (!check_args_valid(argc, argv))
		return (printf ("Error: Make sure to enter positive numbers only\n"));
	count = ft_atoi(argv[1]);
	if (count == 0)
		return (printf ("Error: At least 1 philosopher required\n"));
	forks = init_fork(count, &forks);
	if (!forks)
		return (printf ("Error: Failed to initialize forks\n"));
	env = init_env(argv);
	philo = init_philo(count, forks, &env);
	if (!philo)
		return (printf ("Error: Failed to initialize philosophers\n"));
	start_routine(philo, count);
	return (0);
}
