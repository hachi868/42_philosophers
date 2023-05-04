/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/05 02:52:35 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_living(t_philo_info *philo)
{
	long long tm = get_timestamp();
	printf("check_living start: %lld\n", tm);
	usleep(philo->ctx_simulation->time_to_die * 1000);
	printf("check_living end: %lld\n", tm);
	//is_died(philo);
}

static void	*thread_monitoring(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	check_living(philo);
	//todo:食べ始めたらreturnさせるようなことはできないか？
	return (NULL);
}

void	init_monitoring(t_philo_info *philo)
{
	philo->monitoring = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo->monitoring, NULL, thread_monitoring, (void *)philo) != 0)
	{
		printf("Error!スレッド作れなかった");
		//todo:free
		return ;//error
	}
}

void	is_died(t_philo_info *philo)
{
	//todo:諸々free
	printf("%lld %d died", get_timestamp(), philo->index);
}