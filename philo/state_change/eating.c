/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 19:40:32 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_status	do_take_a_fork(t_philo_info *philo)
{
	if (check_end_and_print(philo, TAKE_A_FORK))
		return (ENDED);
	return (NOT_ENDED);
}

static t_status	do_eat(t_philo_info *philo)
{
	if (check_end_and_print(philo, EAT))
		return (ENDED);
	//食べ始めで死亡監視はじめ
	init_monitoring(philo);
	usleep_with_precision(philo->ctx_simulation, philo->ctx_simulation->time_to_eat);
	return (NOT_ENDED);
}

//食べた回数のチェック
static bool	check_each_eaten(t_philo_info *philo)
{
	t_simulation	*ctx_simulation;

	ctx_simulation = philo->ctx_simulation;
	philo->count_eaten++;
	if (philo->count_eaten == \
		philo->ctx_simulation->number_of_times_each_philosopher_must_eat)
	{
		lock_mutex(\
			&ctx_simulation->mutex_fill_eat, &ctx_simulation->is_lock_fill_eat);
		philo->ctx_simulation->number_fill_eat++;
		if (philo->ctx_simulation->number_fill_eat == \
			philo->ctx_simulation->number_of_philosophers)
		{
			lock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
			philo->ctx_simulation->is_end = true;
			unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
			printf("Simulation stops: "
				"All philosophers have eaten at least %d times\n", \
				ctx_simulation->number_of_times_each_philosopher_must_eat);
			//free_all_at_last(philo->ctx_simulation);//todo:セグフォ
			return (true);
		}
		unlock_mutex(\
			&ctx_simulation->mutex_fill_eat, &ctx_simulation->is_lock_fill_eat);
	}
	return (false);
}

//todo: ENDEDの時は返り先でunlock_mutex_all(philo->ctx_simulation)でもよいかも。
static	void	unlock_spork_and_fork(t_philo_info *philo)
{
	t_simulation	*ctx_simulation;
	int				i_spork;
	int				i_fork;

	ctx_simulation = philo->ctx_simulation;
	i_fork = philo->fork;
	i_spork = philo->spork;
	unlock_mutex(\
		&ctx_simulation->fork_list[i_fork], \
		&ctx_simulation->is_lock_fork[i_fork]);
	unlock_mutex(\
		&ctx_simulation->fork_list[i_spork], \
		&ctx_simulation->is_lock_fork[i_spork]);
}

t_status	do_fork_and_eat(t_philo_info *philo)
{
	t_simulation	*ctx_simulation;
	int				i_spork;
	int				i_fork;

	ctx_simulation = philo->ctx_simulation;
	i_fork = philo->fork;
	i_spork = philo->spork;
	lock_mutex(\
		&ctx_simulation->fork_list[i_spork], \
		&ctx_simulation->is_lock_fork[i_spork]);
	if (do_take_a_fork(philo) == ENDED)
	{
		unlock_mutex(\
			&ctx_simulation->fork_list[i_spork], \
			&ctx_simulation->is_lock_fork[i_spork]);
		return (ENDED);
	}
	lock_mutex(\
		&ctx_simulation->fork_list[i_fork], \
		&ctx_simulation->is_lock_fork[i_fork]);
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
	{
		unlock_mutex_all(philo->ctx_simulation);
		return (ENDED);
	}
	return (NOT_ENDED);
}
