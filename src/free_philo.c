/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:42:44 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 19:18:50 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_philo(t_philo **philo, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		// if (pthread_join (philo[i]->th, NULL))
		// 	perror ("Error");
		pthread_detach (philo[i]->th);
		i++;
	}
}
