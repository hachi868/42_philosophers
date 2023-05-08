/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/07 22:31:51 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	take_a_fork(t_simulation *ctx_simulation, int index)
{
	if (check_end(ctx_simulation))
		return (1);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
	return (0);
}

static int	setup_eating(t_simulation *ctx_simulation, t_philo_info *philo)
{
	if (check_end(ctx_simulation))
		return (1);
	philo->time_last_eaten = get_timestamp();
	init_monitoring(philo);
	printf("%lld %d is eating\n", philo->time_last_eaten, philo->index);
	usleep(ctx_simulation->time_to_eat * 1000);
	return (0);
}

static void	check_each_eaten(t_simulation *ctx_simulation, t_philo_info *philo)
{
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
			//printf("全員たべきった。end!!!\n");
			pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
			free_all_at_last(philo->ctx_simulation);//todo:ここではなく戻り先がよいかも
			//exit(0);//todo:諸々free(ifを抜けないならunlockも？)
		}
		pthread_mutex_unlock(ctx_simulation->mutex_fill_eat);
	}
}

int	do_eat(t_simulation *ctx_simulation, t_philo_info *philo)
{
	if (check_end(ctx_simulation))
		return (1);
	pthread_mutex_lock(philo->spork);
	if (take_a_fork(ctx_simulation, philo->index) == 1)
	{
		pthread_mutex_unlock(philo->spork);
		return (1);
	}
	pthread_mutex_lock(philo->folk);
	if (take_a_fork(ctx_simulation, philo->index) == 1)
	{
		pthread_mutex_unlock(philo->spork);
		pthread_mutex_unlock(philo->folk);
		return (1);
	}
	if (setup_eating(ctx_simulation, philo) == 1)
		return (1);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
		check_each_eaten(ctx_simulation, philo);
	pthread_mutex_unlock(philo->folk);
	pthread_mutex_unlock(philo->spork);
	return (0);
}
