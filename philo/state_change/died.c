/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:42 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 03:27:29 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	is_died(t_philo_info *philo)
{
	printf("%lld %d died", get_timestamp(), philo->index);
}