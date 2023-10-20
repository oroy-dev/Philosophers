/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:22:37 by oroy              #+#    #+#             */
/*   Updated: 2023/10/20 14:41:56 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_philo(t_philo *philo, int count)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&philo->fork) != 0)
			printf ("Error: Couldn't destroy mutex");
		tmp = philo;
		philo = philo->next;
		free (tmp);
		tmp = NULL;
		i++;
	}
}
