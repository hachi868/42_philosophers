/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:12:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 18:28:49 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	unlock_mutex_all(t_simulation *ctx_simulation)
{
	int	i;

	printf("unlock_mutex_all\n");
	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		unlock_mutex(\
			&ctx_simulation->philo_list[i]->spork, \
			&ctx_simulation->philo_list[i]->is_lock_spork);
		unlock_mutex(\
			&ctx_simulation->philo_list[i]->fork, \
			&ctx_simulation->philo_list[i]->is_lock_fork);
		pthread_mutex_destroy(ctx_simulation->fork_list[i]);
		i++;
	}
	unlock_mutex(\
			&ctx_simulation->mutex_fill_eat, \
			&ctx_simulation->is_lock_fill_eat);
	pthread_mutex_destroy(ctx_simulation->mutex_fill_eat);
	unlock_mutex(\
			&ctx_simulation->mutex_is_end, \
			&ctx_simulation->is_lock_is_end);
	pthread_mutex_destroy(ctx_simulation->mutex_is_end);
	return (0);
}

int	lock_mutex(pthread_mutex_t **mutex, bool *is_lock)
{
	if (*is_lock == false)
	{
		pthread_mutex_lock(*mutex);
		*is_lock = true;
	}
	return (0);
}

int	unlock_mutex(pthread_mutex_t **mutex, bool *is_lock)
{
	if (*is_lock == true)
	{
		pthread_mutex_unlock(*mutex);
		*is_lock = false;
	}
	return (0);
}