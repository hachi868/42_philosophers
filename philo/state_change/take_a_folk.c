/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_folk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:49:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 03:29:30 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_take_a_fork(t_philo_info *philo)
{
	printf("%lld %d has taken a fork\n", get_timestamp(), philo->index);
}