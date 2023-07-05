/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/05 10:12:52 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_ctx_simulation(t_simulation *ctx_simulation)
{
	free_and_null((void *)&ctx_simulation->is_lock_fork);
	free_and_null((void *)&ctx_simulation->philo_list);
	free_and_null((void *)&ctx_simulation->fork_list);
	free_and_null((void *)&ctx_simulation->mutex_is_end);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
		free_and_null((void *)&ctx_simulation->mutex_fill_eat);
	free_and_null((void *)&ctx_simulation);
}

void	free_all_at_last(t_simulation *ctx_simulation)
{
	int	i;

	printf("free_all_at_last\n");
	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		free_and_null((void *)&ctx_simulation->fork_list[i]);
		free_and_null((void *)&ctx_simulation->philo_list[i]->thread);
		free_and_null((void *)&ctx_simulation->philo_list[i]->monitoring);
		free_and_null((void *)&ctx_simulation->philo_list[i]);
		i++;
	}
	free_ctx_simulation(ctx_simulation);
	printf("free_all_at_last end\n");
}

void	free_and_null(void **ptr)
{
	if (*ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}
