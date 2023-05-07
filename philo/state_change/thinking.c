/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:27 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/08 02:08:56 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	do_think(t_philo_info *philo)
{
	if (check_end(philo->ctx_simulation))
		return (1);
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	if (philo->ctx_simulation->number_of_philosophers % 2 == 0)
		return (0);
	if (philo->time_to_think > 0)
	{
		usleep(philo->time_to_think * 1000);
		philo->time_to_think = 0;
	}
	else
		philo->time_to_think = philo->ctx_simulation->time_to_eat;
	return (0);
}
