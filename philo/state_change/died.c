/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/03 17:11:38 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// 生死確認 本体
void	check_living(t_simulation *ctx_simulation, t_philo_info *philo)
{
	long long		tm;
	long long		time_limit;

	time_limit = ctx_simulation->time_to_die;
	printf("check_living %lld %lld\n", philo->time_last_eaten, time_limit);
	usleep_with_precision(ctx_simulation, time_limit);
	//is_end mutex
	pthread_mutex_lock(ctx_simulation->mutex_is_end);
	if (ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(ctx_simulation->mutex_is_end);
		return ;
	}
	tm = get_timestamp();
	printf("%lld > %lld\n", tm - time_limit, philo->time_last_eaten);
	//タイムリミットover is_end = true
	if (tm - time_limit > philo->time_last_eaten)
	{
		ctx_simulation->is_end = true;
		is_died(philo);
		pthread_mutex_unlock(ctx_simulation->mutex_is_end);
		return ;
	}
	pthread_mutex_unlock(ctx_simulation->mutex_is_end);
}

//チェック関数
static void	*thread_monitoring(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	check_living(philo->ctx_simulation, philo);
	return (NULL);
}

//死亡監視 init
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

//訃報
void	is_died(t_philo_info *philo)
{
	printf("%lld %d died\n", \
		get_timestamp_diff(philo->ctx_simulation), philo->index);
}
