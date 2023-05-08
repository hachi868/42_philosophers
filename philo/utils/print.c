/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:48:22 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/09 02:06:15 by hachi-gbg        ###   ########.fr       */
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

bool	check_end_and_print(t_philo_info *philo, t_action action)
{
	char		*message;
	long long	timestamp;

	pthread_mutex_lock(philo->ctx_simulation->mutex_is_end);
	if (philo->ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
		return (true);
	}
	message = get_message(action);
	//todo: message = ""の場合？
	if (action == EAT)
	{
		philo->time_last_eaten = get_timestamp();
		timestamp = philo->time_last_eaten - philo->ctx_simulation->time_start;
	}
	else
		timestamp = get_timestamp_diff(philo->ctx_simulation);
	printf("%lld %d %s\n", timestamp, philo->index, message);
	pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
	return (false);
}
