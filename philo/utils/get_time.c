/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:55:07 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/06/29 00:07:38 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		m_sec;

	gettimeofday(&tv, NULL);
	m_sec = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (m_sec);
}

long long	get_timestamp_diff(t_simulation *ctx_simulation)
{
	return (get_timestamp() - ctx_simulation->time_start);
}

void	usleep_with_precision(t_simulation *ctx_simulation, long long sec_limit)
{
	long long	time_start_usleep;

	time_start_usleep = get_timestamp_diff(ctx_simulation);
	while (get_timestamp_diff(ctx_simulation) - time_start_usleep < sec_limit)
		usleep(10);
}
