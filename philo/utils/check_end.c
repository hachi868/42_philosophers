/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:48:22 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/07 02:12:12 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_end(t_simulation *ctx_simulation)
{
	pthread_mutex_lock(ctx_simulation->mutex_is_end);
	if (ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(ctx_simulation->mutex_is_end);
		return (true);
	}
	pthread_mutex_unlock(ctx_simulation->mutex_is_end);
	return (false);
}
