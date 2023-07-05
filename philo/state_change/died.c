/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 02:28:18 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// 生死確認 本体
void	check_living(t_simulation *ctx_simulation, t_philo_info *philo)
{
	long long		tm;
	long long		time_limit;

	time_limit = ctx_simulation->time_to_die;
	usleep_with_precision(ctx_simulation, time_limit + 1);
	lock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
	if (ctx_simulation->is_end == true)
	{
		unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
		return ;
	}
	tm = get_timestamp_diff(ctx_simulation);
	if (tm - time_limit > philo->time_last_eaten)
	{
		ctx_simulation->is_end = true;
		unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
		printf("%lld %d died\n", \
			get_timestamp_diff(philo->ctx_simulation), philo->index);
		return ;
	}
	unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
}

//チェック関数
static void	*thread_monitoring(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	check_living(philo->ctx_simulation, philo);
	return (NULL);
}

static void	error_exit_monitoring(\
	t_philo_info *philo, pthread_t	*ptr, char *func, char *message)
{
	printf("Error: %s: %s\n", func, message);
	free_and_null((void *)&ptr);
	free_all_at_last(philo->ctx_simulation);
}

//死亡監視 init
void	init_monitoring(t_philo_info *philo)
{
	pthread_t	*monitoring;

	monitoring = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		monitoring, NULL, thread_monitoring, (void *)philo) != 0)
		error_exit_monitoring(philo, monitoring, "init_monitoring", \
		"Failed to create a new thread using pthread_create.");
	if (pthread_detach(*monitoring) != 0)
		error_exit_monitoring(philo, monitoring, "init_monitoring", \
			"Failed to detach the thread using pthread_detach.");
	free_and_null((void *)&monitoring);
}
