/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:22:37 by oroy              #+#    #+#             */
/*   Updated: 2023/10/18 15:22:14 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_free(void *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
}

void	free_threads(pthread_t *threads, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		ft_free(threads[i]);
		i++;
	}
	threads = NULL;
}
