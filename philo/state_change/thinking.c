/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:27 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 03:28:48 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
//timestamp_in_ms X is thinking

void	do_think(t_philo_info *philo)
{
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
}
