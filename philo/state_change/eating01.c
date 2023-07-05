/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 03:53:49 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 03:55:31 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	lock_unlock_spork(t_philo_info *philo, bool is_lock)
{
	t_simulation	*ctx_simulation;
	int				i_spork;

	ctx_simulation = philo->ctx_simulation;
	i_spork = philo->spork;
	if (is_lock == LOCK)
	{
		lock_mutex(\
		&ctx_simulation->fork_list[i_spork], \
		&ctx_simulation->is_lock_fork[i_spork]);
	}
	else
	{
		unlock_mutex(\
		&ctx_simulation->fork_list[i_spork], \
		&ctx_simulation->is_lock_fork[i_spork]);
	}
}

static void	lock_unlock_fork(t_philo_info *philo, bool is_lock)
{
	t_simulation	*ctx_simulation;
	int				i_fork;

	ctx_simulation = philo->ctx_simulation;
	i_fork = philo->fork;
	if (is_lock == LOCK)
	{
		lock_mutex(\
		&ctx_simulation->fork_list[i_fork], \
		&ctx_simulation->is_lock_fork[i_fork]);
	}
	else
	{
		unlock_mutex(\
		&ctx_simulation->fork_list[i_fork], \
		&ctx_simulation->is_lock_fork[i_fork]);
	}
}

static void	unlock_spork_and_fork(t_philo_info *philo)
{
	lock_unlock_spork(philo, UNLOCK);
	lock_unlock_fork(philo, UNLOCK);
}

t_status	do_fork_and_eat(t_philo_info *philo)
{
	lock_unlock_spork(philo, LOCK);
	if (do_take_a_fork(philo) == ENDED)
	{
		lock_unlock_spork(philo, UNLOCK);
		return (ENDED);
	}
	lock_unlock_fork(philo, LOCK);
	if (do_take_a_fork(philo) == ENDED)
	{
		unlock_spork_and_fork(philo);
		return (ENDED);
	}
	if (do_eat(philo) == ENDED)
	{
		unlock_spork_and_fork(philo);
		return (ENDED);
	}
	unlock_spork_and_fork(philo);
	if (philo->ctx_simulation->number_of_times_each_philosopher_must_eat > 0 \
		&& check_each_eaten(philo) == true)
		return (ENDED);
	return (NOT_ENDED);
}
