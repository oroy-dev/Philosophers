/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:03:53 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 20:00:43 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_free(void *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
	return (ptr);
}

void	*free_forks(t_fork **forks)
{
	int	i;

	i = 0;
	while (forks[i])
	{
		pthread_mutex_destroy (&forks[i]->mutex);
		ft_free(forks[i]);
		i++;
	}
	return (ft_free(forks));
}

void	*free_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		ft_free(philo[i]);
		i++;
	}
	return (ft_free(philo));
}

void	free_all(t_philo **philo, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_join (philo[i]->th, NULL);
		i++;
	}
}
