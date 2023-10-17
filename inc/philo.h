/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:39:58 by oroy              #+#    #+#             */
/*   Updated: 2023/10/16 22:05:21 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	*threads;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_times;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_free(void *ptr);

#endif