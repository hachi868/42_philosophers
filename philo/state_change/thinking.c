/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:27 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/06 03:14:45 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	do_think(t_philo_info *philo)
{
	check_end(philo->ctx_simulation);
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	usleep(100000);//todo:停止時間検討
}
