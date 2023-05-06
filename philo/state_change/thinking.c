/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:05:27 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/07 03:05:14 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	do_think(t_philo_info *philo)
{
	if (check_end(philo->ctx_simulation))
		return (1);
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	usleep(100);//todo:停止時間検討
	return (0);
}
