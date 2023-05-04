/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 15:54:42 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	is_each_fill_must_eat(t_simulation *ctx_simulation)
{
	t_philo_info	*cr_philo;

	is_fill = true;
	cr_philo = ctx_simulation->philo_head;
	while (cr_philo)
	{
		if (cr_philo->count_eaten < \
			ctx_simulation->number_of_times_each_philosopher_must_eat)
			return (false);
		cr_philo = cr_philo->next;
	}
	return (true);
}

void	do_eat(t_simulation *ctx_simulation, t_philo_info *philo)
{
	t_philo_info	*cr_philo;
	bool			is_fill_must_eat;
	int				must_eat;

	must_eat = ctx_simulation -> number_of_times_each_philosopher_must_eat;
	cr_philo = ctx_simulation -> philo_head;
	is_fill_must_eat = false;
	philo -> time_last_eaten = get_timestamp();
	philo -> count_eaten++;
	printf("%lld %d is eating\n", philo -> time_last_eaten, philo->index + 1);
	if (philo -> count_eaten == must_eat)
	{
		is_fill_must_eat = true;
		while (cr_philo)
		{
			if (cr_philo -> count_eaten < must_eat)
			{
				is_fill_must_eat = false;
				break ;
			}
			cr_philo = cr_philo -> next;
		}
		if (is_fill_must_eat == true)
		{
			//todo: 全員規定の回数食事をしたのでシミュレーション終了する
		}
	}
}
