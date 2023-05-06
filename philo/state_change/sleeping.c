/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/07 02:18:39 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	do_sleep(t_simulation *ctx_simulation, t_philo_info *philo)
{
	if (check_end(ctx_simulation))
		return (1);
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
	usleep(ctx_simulation->time_to_sleep * 1000);
	return (0);
}
