/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/09 14:03:28 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_status	do_take_a_fork(t_philo_info *philo)
{
	if (check_end_and_print(philo, TAKE_A_FORK))
		return (ENDED);
	return (NOT_ENDED);
}

t_status	do_eat(t_philo_info *philo)
{
	if (check_end_and_print(philo, EAT))
		return (ENDED);
	init_monitoring(philo);
	usleep_with_precision(\
		philo->ctx_simulation, philo->ctx_simulation->time_to_eat);
	return (NOT_ENDED);
}

void	is_fill_eat(t_simulation *ctx_simulation, t_philo_info *philo)
{
	pthread_mutex_lock(ctx_simulation->mutex_is_end);
	philo->ctx_simulation->is_end = true;
	unlock_mutex(ctx_simulation->mutex_is_end, "is_end");
	printf("Simulation stops: "
		"All philosophers have eaten at least %d times.\n", \
		ctx_simulation->number_of_times_each_philosopher_must_eat);
	unlock_mutex_all(philo->ctx_simulation);
}

bool	check_each_eaten(t_philo_info *philo)
{
	t_simulation	*ctx_simulation;

	ctx_simulation = philo->ctx_simulation;
	philo->count_eaten++;
	if (philo->count_eaten == \
		philo->ctx_simulation->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(ctx_simulation->mutex_fill_eat);
		philo->ctx_simulation->number_fill_eat++;
		if (philo->ctx_simulation->number_fill_eat == \
			philo->ctx_simulation->number_of_philosophers)
		{
			is_fill_eat(ctx_simulation, philo);
			return (true);
		}
		unlock_mutex(ctx_simulation->mutex_fill_eat, "fill_eat");
	}
	return (false);
}
