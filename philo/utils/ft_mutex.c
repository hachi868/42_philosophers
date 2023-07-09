/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:12:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/09 14:04:08 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	unlock_mutex_all(t_simulation *ctx_simulation)
{
	int	i;

	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		unlock_mutex(ctx_simulation->fork_list[i], "fork_list[i]");
		pthread_mutex_destroy(ctx_simulation->fork_list[i]);
		i++;
	}
	unlock_mutex(ctx_simulation->mutex_is_end, "is_end");
	pthread_mutex_destroy(ctx_simulation->mutex_is_end);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
	{
		unlock_mutex(ctx_simulation->mutex_fill_eat, "fill_eat");
		pthread_mutex_destroy(ctx_simulation->mutex_fill_eat);
	}
	return (0);
}

int	unlock_mutex(pthread_mutex_t *cr_mutex, char *name_func)
{
	int	status;

	status = pthread_mutex_unlock(cr_mutex);
	if (status != 0)
		printf("unlock error: %s\n", name_func);
	return (status);
}
