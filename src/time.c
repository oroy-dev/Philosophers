/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:14:19 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 14:41:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int	get_time(void)
{
	static struct timeval	begin = {0, 0};
	struct timeval			now;
	long int				time;

	if (begin.tv_sec == 0 && begin.tv_usec == 0)
		gettimeofday (&begin, NULL);
	gettimeofday (&now, NULL);
	time = (now.tv_sec * 1000000 + now.tv_usec) -
		(begin.tv_sec * 1000000 + begin.tv_usec);
	return (time * 0.001);
}

void	usleep_iterate(long int usleep_total)
{
	long int	start_time;

	start_time = get_time();
	while (get_time() - start_time < usleep_total)
		usleep (200);
}
