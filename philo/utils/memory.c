/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 11:36:32 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all_at_last(t_simulation *ctx_simulation)
{
	int	i;

	printf("free_all_at_last\n");
	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		free_and_null((void *)&ctx_simulation->philo_list[i]);
		pthread_mutex_destroy(ctx_simulation->folk_list[i]);
		free_and_null((void *)&ctx_simulation->folk_list[i]);
		i++;
	}
}

int	free_and_null(void **ptr)
{
	//printf("free_and_null:1; %p %p\n", ptr, *ptr);
	free(*ptr);
	*ptr = NULL;
	//printf("free_and_null:2; %p %p\n", ptr, *ptr);
	return (0);
}

//void	clear_philo(t_simulation *ctx_simulation)
//{
//
//}