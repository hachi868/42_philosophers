/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:48:22 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 16:20:45 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static char	*get_message(t_action action)
{
	char	*message;

	if (action == TAKE_A_FORK)
		message = "has taken a fork";
	else if (action == EAT)
		message = "is eating";
	else if (action == SLEEP)
		message = "is sleeping";
	else if (action == THINK)
		message = "is thinking";
	else
		message = "";
	return (message);
}

bool	check_end_and_print(\
	t_philo_info *philo, t_action action)
{
	char			*message;
	long long		timestamp;
	t_simulation	*ctx_simulation;

	ctx_simulation = philo->ctx_simulation;
	lock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
	if (ctx_simulation->is_end == true)
	{
		unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
		return (true);
	}
	message = get_message(action);
	if (action == EAT)
	{
		philo->time_last_eaten = get_timestamp_diff(ctx_simulation);
		timestamp = philo->time_last_eaten;
	}
	else
		timestamp = get_timestamp_diff(ctx_simulation);
	printf("%lld %d %s\n", timestamp, philo->index, message);
	unlock_mutex(\
			&ctx_simulation->mutex_is_end, &ctx_simulation->is_lock_is_end);
	return (false);
}
