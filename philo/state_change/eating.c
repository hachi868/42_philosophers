/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/03 17:18:13 by hachi-gbg        ###   ########.fr       */
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
static void	check_each_eaten(t_philo_info *philo)
{
	philo->count_eaten++;
	if (philo->count_eaten == \
		philo->ctx_simulation->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(philo->ctx_simulation->mutex_fill_eat);
		philo->ctx_simulation->number_fill_eat++;
		//全員食べきってis_end
		if (philo->ctx_simulation->number_fill_eat == \
			philo->ctx_simulation->number_of_philosophers)
		{
			pthread_mutex_lock(philo->ctx_simulation->mutex_is_end);
			philo->ctx_simulation->is_end = true;
			//printf("全員たべきった。end!!!\n");
			pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
			free_all_at_last(philo->ctx_simulation);//todo:ここではなく戻り先がよいかも
			//exit(0);//todo:諸々free(ifを抜けないならunlockも？)
		}
		pthread_mutex_unlock(philo->ctx_simulation->mutex_fill_eat);
	}
}

t_status	do_fork_and_eat(t_philo_info *philo)
{
	//フォークmutexlockしつつ1本ずつ取る。利き手じゃない方から。
	pthread_mutex_lock(philo->spork);
	if (do_take_a_fork(philo) == ENDED)
	{
		pthread_mutex_unlock(philo->spork);
		return (ENDED);
	}
	pthread_mutex_lock(philo->folk);
	if (do_take_a_fork(philo) == ENDED)
	{
		pthread_mutex_unlock(philo->spork);
		pthread_mutex_unlock(philo->folk);
		return (ENDED);
	}
	if (do_eat(philo) == ENDED)
		return (ENDED);
	if (philo->ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
		check_each_eaten(philo);
	pthread_mutex_unlock(philo->folk);
	pthread_mutex_unlock(philo->spork);
	return (NOT_ENDED);
}
