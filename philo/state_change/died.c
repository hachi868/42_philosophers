/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/08 01:58:58 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_living(t_philo_info *philo)
{
	long long	tm;
	long long	time_limit;

	time_limit = philo->ctx_simulation->time_to_die;
	usleep(time_limit * 1000);
	pthread_mutex_lock(philo->ctx_simulation->mutex_is_end);
	if (philo->ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
		return ;
	}
	tm = get_timestamp();
	if (tm - time_limit > philo->time_last_eaten)
	{
		philo->ctx_simulation->is_end = true;
		is_died(philo);
		pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
		return ;
	}
	pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
}

static void	*thread_monitoring(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	check_living(philo);
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
	//todo:諸々free
	printf("%lld %d died\n", get_timestamp(), philo->index);
	free_all_at_last(philo->ctx_simulation);
}
