/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:15:28 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 21:26:21 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static int	activate_each_must_eat(\
	t_simulation *ctx_simulation, int argc, int *args)
{
	if (argc == 6)
	{
		if (args[4] == 0)
		{
			printf("Simulation stops:"
				"All philosophers have eaten at least 0 times.\n");
			return (1);
		}
		ctx_simulation->number_of_times_each_philosopher_must_eat = args[4];
	}
	else
		ctx_simulation->number_of_times_each_philosopher_must_eat = -1;
	ctx_simulation->number_fill_eat = 0;
	if (ctx_simulation->number_of_times_each_philosopher_must_eat == -1)
		ctx_simulation->mutex_fill_eat = NULL;
	else
	{
		ctx_simulation->mutex_fill_eat = \
			(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (ctx_simulation->mutex_fill_eat == NULL)
			return (1);
		if (pthread_mutex_init(ctx_simulation->mutex_fill_eat, NULL) != 0)
			return (1);
	}
	return (0);
}

static int	malloc_list_philo_fork(t_simulation *ctx_simulation)
{
	int	i;

	i = 0;
	while (i < ctx_simulation->number_of_philosophers)
	{
		ctx_simulation->philo_list[i] = \
			(t_philo_info *)malloc(sizeof(t_philo_info));
		if (ctx_simulation->philo_list[i] == NULL)
			return (1);
		ctx_simulation->fork_list[i] = \
			(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (ctx_simulation->fork_list[i] == NULL)
			return (1);
		ctx_simulation->is_lock_fork[i] = false;
		i++;
	}
	return (0);
}

static t_simulation	*init_simulation(int argc, int *args)
{
	t_simulation	*ctx_simulation;

	ctx_simulation = (t_simulation *)malloc(sizeof(t_simulation));
	if (activate_each_must_eat(ctx_simulation, argc, args) == 1)
		free_all_error(ctx_simulation);
	ctx_simulation->number_of_philosophers = args[0];
	ctx_simulation->philo_list = (t_philo_info **)malloc(\
		sizeof(t_philo_info *) * ctx_simulation->number_of_philosophers);
	ctx_simulation->fork_list = (pthread_mutex_t **)malloc(\
		sizeof(pthread_mutex_t *) * ctx_simulation->number_of_philosophers);
	ctx_simulation->is_lock_fork = (bool *)malloc(\
		sizeof(bool) * ctx_simulation->number_of_philosophers);
	if (malloc_list_philo_fork(ctx_simulation) == 1)
		free_all_error(ctx_simulation);
	ctx_simulation->time_to_die = args[1];
	ctx_simulation->time_to_eat = args[2];
	ctx_simulation->time_to_sleep = args[3];
	ctx_simulation->is_end = false;
	ctx_simulation->mutex_is_end = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (ctx_simulation->mutex_is_end == NULL)
		free_all_error(ctx_simulation);
	if (pthread_mutex_init(ctx_simulation->mutex_is_end, NULL) != 0)
		free_all_error(ctx_simulation);
	free_args(argc, &args);
	return (ctx_simulation);
}

int	main(int argc, char **argv)
{
	int				*args;
	t_simulation	*ctx_simulation;

	if (argc == 5 || argc == 6)
	{
		// 引数チェック
		args = (int *)malloc(sizeof(int) * argc);
		if (is_invalid_args(argc, argv, args) == false)
			return (1); // todo:end,show_error?
		// OKならシミュレーション開始
		ctx_simulation = init_simulation(argc, args);
		if (ctx_simulation == NULL)
			return (1);
		start_simulation(ctx_simulation);
	}
	return (0);
}
