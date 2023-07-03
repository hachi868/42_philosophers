/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:48:22 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/03 18:07:20 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static char *get_message(t_action action)
{
	char *message;

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

// ここで死ぬことはない。前の動作の結果、is_endになっていないかチェックしている。
// 動作後に死ぬならtrueが返る。生きるならメッセージ表示してfalse
bool check_end_and_print(t_philo_info *philo, t_action action)
{
	char *message;
	long long timestamp;

	pthread_mutex_lock(philo->ctx_simulation->mutex_is_end);
	// is_end
	if (philo->ctx_simulation->is_end == true)
	{
		pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
		return (true);
	}
	// まだis_endじゃない
	message = get_message(action);
	// todo: message = ""の場合？
	// EATの場合、食べ終わりでここにきている？
	if (action == EAT)
	{
		philo->time_last_eaten = get_timestamp_diff(philo->ctx_simulation);
		timestamp = philo->time_last_eaten;
	}
	else
	{
		timestamp = get_timestamp_diff(philo->ctx_simulation);
	}
	printf("%lld %d %s\n", timestamp, philo->index, message);
	pthread_mutex_unlock(philo->ctx_simulation->mutex_is_end);
	return (false);
}
