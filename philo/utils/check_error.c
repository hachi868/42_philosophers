/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:39:11 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/16 03:04:11 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	free_args(int argc, int **ptr)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		free(*ptr);
		*ptr = NULL;
		i++;
	}
	return (0);
}

bool	is_invalid_args(int argc, char **argv, int *args)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		args[i] = ft_atoi_unsigned(argv[i + 1]);
		if (args[i] < 0)
		{
			free_args(argc, &args);
			return (false);
		}
		i++;
	}
	return (true);
}
