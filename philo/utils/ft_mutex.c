/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:12:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 22:20:31 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	unlock_mutex_all(t_simulation *ctx_simulation)
{
	int	i;

	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		unlock_mutex(\
			&ctx_simulation->fork_list[i], \
			&ctx_simulation->is_lock_fork[i]);
		pthread_mutex_destroy(ctx_simulation->fork_list[i]);
		i++;
	}
	unlock_mutex(\
			&ctx_simulation->mutex_is_end, \
			&ctx_simulation->is_lock_is_end);
	pthread_mutex_destroy(ctx_simulation->mutex_is_end);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
	{
		unlock_mutex(\
			&ctx_simulation->mutex_fill_eat, \
			&ctx_simulation->is_lock_fill_eat);
		pthread_mutex_destroy(ctx_simulation->mutex_fill_eat);
	}
	return (0);
}

int	lock_mutex(pthread_mutex_t **mutex, bool *is_lock)
{
	pthread_mutex_lock(*mutex);
	//todo: lockされていた場合
	if (*is_lock == false)
		*is_lock = true;
	return (0);
}

int	unlock_mutex(pthread_mutex_t **mutex, bool *is_lock)
{
	pthread_mutex_unlock(*mutex);
	if (*is_lock == true)
		*is_lock = false;
	return (0);
}