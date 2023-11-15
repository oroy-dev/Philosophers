/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:30:30 by oroy              #+#    #+#             */
/*   Updated: 2023/11/15 11:16:40 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	if (!str)
		return (-1);
	i = 0;
	num = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (num);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	total;
	size_t	i;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	i = 0;
	total = count * size;
	mem = malloc(total);
	if (!mem)
		return (NULL);
	while (i < total)
	{
		*((unsigned char *)mem + i) = '\0';
		i++;
	}
	return (mem);
}

void	*ft_free(void *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
	return (NULL);
}
