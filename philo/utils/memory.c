/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 23:14:50 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all_error(t_simulation *ctx_simulation)
{
	int	i;

	printf("free_all_error\n");
	i = 0;
	//unlock_mutex_all(ctx_simulation);//todo: ここに入る前に終わらせておきたい（スレッド終了奴）
	while (i < ctx_simulation->number_of_philosophers)
	{
		free_and_null((void *)&ctx_simulation->philo_list[i]);
		free_and_null((void *)&ctx_simulation->fork_list[i]);
		i++;
	}
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
		free_and_null((void *)&ctx_simulation->philo_list[i]);
		i++;
	}
	free_and_null((void *)&ctx_simulation->is_lock_fork);
	free_and_null((void *)&ctx_simulation->philo_list);
	free_and_null((void *)&ctx_simulation->fork_list);
	free_and_null((void *)&ctx_simulation->mutex_is_end);
	if (ctx_simulation->number_of_times_each_philosopher_must_eat > 0)
		free_and_null((void *)&ctx_simulation->mutex_fill_eat);
	free_and_null((void *)&ctx_simulation);
	printf("free_all_at_last end\n");
}

int	free_and_null(void **ptr)
{
	if (*ptr == NULL)
		return (0);
	//printf("free_and_null:1; %p %p\n", ptr, *ptr);
	free(*ptr);
	*ptr = NULL;
	//printf("free_and_null:2; %p %p\n", ptr, *ptr);
	return (0);
}

//void	clear_philo(t_simulation *ctx_simulation)
//{
//
//}