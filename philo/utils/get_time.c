/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:55:07 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 01:05:51 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// ミリ秒取得
long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		m_sec;

	gettimeofday(&tv, NULL);
	m_sec = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (m_sec);
}

// 開始からの時間
long long	get_timestamp_diff(t_simulation *ctx_simulation)
{
	return (get_timestamp() - ctx_simulation->time_start);
}

// 調整入りusleep
void	usleep_with_precision(t_simulation *ctx_simulation, long long sec_limit)
{
	long long	time_start_usleep;

	time_start_usleep = get_timestamp_diff(ctx_simulation);
	while (get_timestamp_diff(ctx_simulation) - time_start_usleep < sec_limit)
		usleep(100);
}
