/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:39:11 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 16:17:18 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_invalid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}