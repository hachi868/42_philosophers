/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:12:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 17:34:21 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	unlock_mutex_all(t_simulation *ctx_simulation)
{
	int	i;

	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		pthread_mutex_unlock(ctx_simulation->fork_list[i]);
		pthread_mutex_destroy(ctx_simulation->fork_list[i]);
		i++;
	}
	pthread_mutex_unlock(ctx_simulation->mutex_is_end);
	pthread_mutex_destroy(ctx_simulation->mutex_is_end);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_unlock(ctx_simulation->mutex_fill_eat);
		pthread_mutex_destroy(ctx_simulation->mutex_fill_eat);
	}
	return (0);
}
