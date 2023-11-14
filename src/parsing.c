/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:03:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/13 18:56:45 by oroy             ###   ########.fr       */
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

int	validate_args(int argc, char **argv)
{
	int	num;
	int	i;

	if (argc < 5 || argc > 6)
		return (printf ("Error: 5 or 6 arguments required\n"));
	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (i == 1 && num < 1)
			return (printf ("Error: At least 1 philosopher required\n"));
		else if (num == -1)
			return (printf ("Error: Enter positive numbers only\n"));
		i++;
	}
	return (0);
}
