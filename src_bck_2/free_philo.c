/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:22:37 by oroy              #+#    #+#             */
/*   Updated: 2023/10/25 15:17:05 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/philo.h"

// int	free_philo(t_philo *philo, int count)
// {
// 	t_philo	*tmp;
// 	int		i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		if (pthread_mutex_destroy(&philo->mutex) != 0)
// 			printf ("Error: Couldn't destroy mutex");
// 		tmp = philo;
// 		philo = philo->next;
// 		free (tmp);
// 		tmp = NULL;
// 		i++;
// 	}
// 	return (0);
// }
