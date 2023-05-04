/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:04:58 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 17:02:55 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	is_each_fill_must_eat(t_simulation *ctx_simulation)
{
	t_philo_info	*cr_philo;

	cr_philo = ctx_simulation->philo_list[0];
	while (cr_philo)
	{
		if (cr_philo->count_eaten < \
			ctx_simulation->number_of_times_each_philosopher_must_eat)
			return (0);
		cr_philo++;
	}
	return (1);
}

void	do_eat(t_simulation *ctx_simulation, t_philo_info *philo)
{
	t_philo_info	*cr_philo;
	int				is_fill_must_eat;
	int				must_eat;

	must_eat = ctx_simulation->number_of_times_each_philosopher_must_eat;
	cr_philo = ctx_simulation->philo_list[0];
	is_fill_must_eat = 0;
	philo->time_last_eaten = get_timestamp();
	printf("%lld %d is eating\n", philo->time_last_eaten, philo->index);
	usleep(ctx_simulation->time_to_eat * 1000);
	philo->count_eaten++;
	if (philo->count_eaten == must_eat)
	{
		is_fill_must_eat = 1;
		while (cr_philo)
		{
			if (cr_philo->count_eaten < must_eat)
			{
				is_fill_must_eat = 0;
				break ;
			}
			cr_philo++;
		}
		if (is_fill_must_eat == 1)
		{
			is_each_fill_must_eat(ctx_simulation);
			//todo: 全員規定の回数食事をしたのでシミュレーション終了する
		}
	}
}
