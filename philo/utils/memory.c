/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/10 22:27:19 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all_at_last(t_simulation *ctx_simulation)
{
	int	i;

	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		free_and_null(&ctx_simulation->philo_list[i]);
		pthread_mutex_destroy(ctx_simulation->folk_list[i]);
		free_and_null2(&ctx_simulation->folk_list[i]);
		i++;
	}
}

int	free_and_null(t_philo_info **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (0);
}

int	free_and_null2(pthread_mutex_t **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (0);
}

//void	clear_philo(t_simulation *ctx_simulation)
//{
//
//}