/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:15:28 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/16 03:06:05 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static t_simulation	*init_simulation(int argc, int *args)
{
	t_simulation	*ctx_simulation;
	int				i;

	i = 0;
	ctx_simulation = (t_simulation *)malloc(sizeof(t_simulation));
	ctx_simulation->number_of_philosophers = args[0];
	ctx_simulation->philo_list = (t_philo_info **)malloc(\
		sizeof(t_philo_info *) * ctx_simulation->number_of_philosophers);
	ctx_simulation->folk_list = (pthread_mutex_t **)malloc(\
		sizeof(pthread_mutex_t *) * ctx_simulation->number_of_philosophers);
	while (i < ctx_simulation->number_of_philosophers)
	{
		ctx_simulation->philo_list[i] = \
			(t_philo_info *)malloc(sizeof(t_philo_info));
		ctx_simulation->folk_list[i] = \
			(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		i++;
	}
	ctx_simulation->time_to_die = args[1];
	ctx_simulation->time_to_eat = args[2];
	ctx_simulation->time_to_sleep = args[3];
	if (argc == 6)
		ctx_simulation->number_of_times_each_philosopher_must_eat = args[4];
	else
		ctx_simulation->number_of_times_each_philosopher_must_eat = -1;
	//todo: 0の場合は開始即終了
	ctx_simulation->number_fill_eat = 0;
	ctx_simulation->mutex_fill_eat = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(ctx_simulation->mutex_fill_eat, NULL) != 0)
		exit(1);//todo:free
	ctx_simulation->is_end = false;
	ctx_simulation->mutex_is_end = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(ctx_simulation->mutex_is_end, NULL) != 0)
		exit(1);//todo:free
	free_args(argc, &args);
	return (ctx_simulation);
}

int	main(int argc, char **argv)
{
	int				*args;
	t_simulation	*ctx_simulation;

	if (argc == 5 || argc == 6)
	{
		args = (int *)malloc(sizeof(int) * argc);
		if (is_invalid_args(argc, argv, args) == false)
			return (1);//todo:end,show_error?
		ctx_simulation = init_simulation(argc, args);
		if (ctx_simulation == NULL)
			return (1);
		start_simulation(ctx_simulation);
	}
	return (0);
}