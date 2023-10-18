/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:50:42 by oroy              #+#    #+#             */
/*   Updated: 2023/10/18 16:12:28 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *forks)
{
	printf ("Philo is eating\n");
}

int	start_routine(t_philo *philo, int thread_count)
{
	int	i;
	int	forks;

	i = 0;
	forks = thread_count;
	while (i < thread_count)
	{
		if (pthread_create (&philo->threads[i], NULL, &routine, &forks))
		{
			free_threads(philo->threads, thread_count);
			return (1);
		}
		i++;
	}
	return (0);
}
