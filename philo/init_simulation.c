/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 22:57:40 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static void	*thread_func(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	if (philo->ctx_simulation->number_of_philosophers % 2 == 1)//奇数なら調整いれる
	{
		if (philo->index == 1)
			usleep(200);
		else if (philo->index % 2 == 0)
			usleep(100);
	}
	// 順に実行
	while (1)
	{
		if (do_fork_and_eat(philo) == ENDED)
			break ;
		if (do_sleep(philo) == ENDED)
			break ;
		if (do_think(philo) == ENDED)
			break ;
	}
	return ((void *)philo);
}

static void	assign_fork(t_philo_info *philo_info, int i)
{
	int	num_philo;

	num_philo = philo_info->ctx_simulation->number_of_philosophers;
	if (i % 2 == 0)
	{
		if (i == num_philo - 1)
			philo_info->spork = 0;
		else
			philo_info->spork = i + 1;
		philo_info->fork = i;
	}
	else
	{
		if (i == num_philo - 1)
			philo_info->fork = 0;
		else
			philo_info->fork = i + 1;
		philo_info->spork = i;
	}
}

//それぞれの哲学者init
int	init_philo(t_simulation *ctx_simulation, int i)
{
	t_philo_info	*philo_info;
	int				num_philo;

	num_philo = ctx_simulation->number_of_philosophers;
	philo_info = ctx_simulation->philo_list[i];
	philo_info->ctx_simulation = ctx_simulation;
	philo_info->index = i + 1;
	assign_fork(philo_info, i);
	philo_info->time_last_eaten = 0;
	philo_info->count_eaten = 0;
	if (num_philo % 2 == 1 && i % 5 < 3)//todo: 奇数人の場合の調整
		philo_info->time_to_think = ctx_simulation->time_to_eat;
	else
		philo_info->time_to_think = 0;
	philo_info->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo_info->thread, NULL, thread_func, (void *)philo_info) != 0)
	{
		printf("Error: init_philo: Failed to create a new thread using pthread_create.\n");
		free_all_error(ctx_simulation);
		return (1);
	}
	init_monitoring(philo_info);
	return (0);
}

int	start_simulation(t_simulation *ctx_simulation)
{
	int	num_threads;
	int	i;

	num_threads = ctx_simulation->number_of_philosophers;
	i = 0;
	while (i < num_threads)
	{
		if (pthread_mutex_init(ctx_simulation->fork_list[i], NULL) != 0)
		{
			free_all_error(ctx_simulation);
			return (1);
		}
		i++;
	}
	ctx_simulation->time_start = get_timestamp();
	i = 0;
	while (i < num_threads)
	{
		init_philo(ctx_simulation, i);
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(*ctx_simulation->philo_list[i]->thread, NULL) != 0)
		{
			printf("Error: start_simulation: "
				"Failed to create a new thread using pthread_join.\n");
			free_all_error(ctx_simulation);
			return (1);
		}
		i++;
	}
	free_all_at_last(ctx_simulation);
	return (0);
}
