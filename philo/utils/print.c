/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:49:37 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/08 22:55:41 by hachi-gbg        ###   ########.fr       */
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