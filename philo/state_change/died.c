/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/06/29 00:03:54 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_living(t_simulation *ctx_simulation, t_philo_info *philo)
{
	long long		tm;
	long long		time_limit;

	time_limit = ctx_simulation->time_to_die;
	usleep_with_precision(ctx_simulation, time_limit);
	pthread_mutex_lock(ctx_simulation->mutex_is_end);
	if (ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(ctx_simulation->mutex_is_end);
		return ;
	}
	tm = get_timestamp();
	if (tm - time_limit > philo->time_last_eaten)
	{
		ctx_simulation->is_end = true;
		is_died(philo);
		pthread_mutex_unlock(ctx_simulation->mutex_is_end);
		return ;
	}
	pthread_mutex_unlock(ctx_simulation->mutex_is_end);
}

static void	*thread_monitoring(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	check_living(philo->ctx_simulation, philo);
	return (NULL);
}

void	init_monitoring(t_philo_info *philo)
{
	pthread_t	*monitoring;

	monitoring = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		monitoring, NULL, thread_monitoring, (void *)philo) != 0)
	{
		printf("Error!スレッド作れなかった init_monitoring\n");
		free(monitoring);
		monitoring = NULL;
		return ;//error
	}
	if (pthread_detach(*monitoring) != 0)
	{
		printf("Error!スレッド待ち失敗");
		free(monitoring);
		monitoring = NULL;
		return ;//error
	}
	free(monitoring);
	monitoring = NULL;
}

void	is_died(t_philo_info *philo)
{
	printf("%lld %d died\n", \
		get_timestamp_diff(philo->ctx_simulation), philo->index);
}
