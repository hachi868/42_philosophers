/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/06 18:45:20 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_a_fork(t_simulation *ctx_simulation, int index)
{
	check_end(ctx_simulation);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
}

void	do_eat(t_simulation *ctx_simulation, t_philo_info *philo)
{
	check_end(ctx_simulation);
	philo->time_last_eaten = get_timestamp();
	init_monitoring(philo);
	printf("%lld %d is eating\n", philo->time_last_eaten, philo->index);
	usleep(ctx_simulation->time_to_eat * 1000);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat == -1)
		return ;
	philo->count_eaten++;
	if (philo->count_eaten == \
		ctx_simulation->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(ctx_simulation->mutex_fill_eat);
		ctx_simulation->number_fill_eat++;
		if (ctx_simulation->number_fill_eat == \
			ctx_simulation->number_of_philosophers)
		{
			pthread_mutex_lock(philo->ctx_simulation->mutex_is_end);
			philo->ctx_simulation->is_end = true;
			printf("全員たべきった。end!!!\n");
			pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
			free_all_at_last(philo->ctx_simulation);
			//exit(0);//todo:諸々free(ifを抜けないならunlockも？)
		}
		pthread_mutex_unlock(ctx_simulation->mutex_fill_eat);
	}
}
