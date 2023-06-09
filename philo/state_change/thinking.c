/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:27 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 12:56:00 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_status	do_think(t_philo_info *philo)
{
	if (check_end_and_print(philo, THINK))
		return (ENDED);
	if (philo->ctx_simulation->number_of_philosophers % 2 == 0)
		return (NOT_ENDED);
	if (philo->time_to_think > 0)
	{
		usleep_with_precision(philo->ctx_simulation, philo->time_to_think);
		philo->time_to_think = 0;
	}
	else
		philo->time_to_think = philo->ctx_simulation->time_to_eat;
	return (NOT_ENDED);
}
