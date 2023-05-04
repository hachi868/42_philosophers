/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 18:48:12 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*check_living(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	usleep(philo->ctx_simulation->time_to_die * 1000);
	//todo: 前回の食事からの時間チェック。というかここまできたということは死では？
	return (NULL);
}

void	init_monitoring(t_simulation *ctx_simulation, t_philo_info *philo)
{
	//todo:すでにあったら強制終了して新しく立ち上げる。
	philo->monitoring = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo->monitoring, NULL, check_living, (void *)philo) != 0)
	{
		printf("Error!スレッド作れなかった");
//todo:free
		return ;//error
	}
}

void	is_died(t_philo_info *philo)
{
	printf("%lld %d died", get_timestamp(), philo->index);
}