/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/23 19:15:57 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_rules	rules;

	rules = *(t_rules *)arg;
	printf ("Philo is eating\n");
	return (NULL);
}

int	start_routine(t_philo *philo, int count, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create (&philo->th, NULL, &routine, (void *)rules))
		{
			free_philo(philo, count);
			return (1);
		}
		i++;
	}
	return (0);
}
