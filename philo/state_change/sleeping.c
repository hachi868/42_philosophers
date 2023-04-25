/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:14 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 03:28:55 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_sleep(t_philo_info *philo)
{
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
}
