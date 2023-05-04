/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_folk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:49:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 16:51:36 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_take_a_fork(t_philo_info *philo)
{
	pthread_mutex_lock(philo->spork);
	printf("%lld %d has taken a fork\n", get_timestamp(), philo->index);
	pthread_mutex_lock(philo->folk);
	printf("%lld %d has taken a fork\n", get_timestamp(), philo->index);
	//todo:eat
	pthread_mutex_unlock(philo->folk);
	pthread_mutex_unlock(philo->spork);
}
