/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 03:28:06 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_eat(t_philo_info *philo)
{
	printf("%lld %d is eating\n", get_timestamp(), philo->index);
}
