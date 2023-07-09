/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:48:22 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/09 14:32:58 by hachi-gbg        ###   ########.fr       */
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
	pthread_mutex_lock(ctx_simulation->mutex_is_end);
	if (ctx_simulation->is_end == true)
	{
		unlock_mutex(ctx_simulation->mutex_is_end, "is_end");
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
	if (strcmp(message, "is eating") == 0)
		printf("%lld %d has taken a fork\n", timestamp, philo->index);
	printf("%lld %d %s\n", timestamp, philo->index, message);
	unlock_mutex(ctx_simulation->mutex_is_end, "is_end");
	return (false);
}
