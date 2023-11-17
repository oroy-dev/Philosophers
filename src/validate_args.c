/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:03:52 by oroy              #+#    #+#             */
/*   Updated: 2023/11/17 15:24:13 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		if (num == -1)
			return (printf ("Error: Enter positive integers only\n"));
		else if (i == 1 && num < 1)
			return (printf ("Error: At least 1 philosopher required\n"));
		else if ((i >= 2 && i <= 4) && num < 1)
			return (printf ("Error: At least 1 ms for time values required\n"));
		i++;
	}
	return (0);
}
