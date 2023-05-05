/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/06 02:51:02 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_sleep(t_simulation *ctx_simulation, t_philo_info *philo)
{
	check_end(ctx_simulation);
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
	usleep(ctx_simulation->time_to_sleep * 1000);
}
