/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:10:31 by oroy              #+#    #+#             */
/*   Updated: 2023/11/10 18:40:30 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock (&philo->env->mutex_print);
	printf (msg, get_time(), philo->id);
	pthread_mutex_unlock (&philo->env->mutex_print);
}
