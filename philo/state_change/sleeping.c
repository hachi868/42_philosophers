/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/06/29 00:02:23 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_status	do_sleep(t_philo_info *philo)
{
	if (check_end_and_print(philo, SLEEP))
		return (ENDED);
	usleep_with_precision(philo->ctx_simulation, philo->ctx_simulation->time_to_sleep);
	return (NOT_ENDED);
}
