/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:15:28 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 17:00:10 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static t_simulation	*init_philo(int argc, char **argv)
{
	t_simulation	*ctx_simulation;
	int			i;

	i = 0;
	ctx_simulation = (t_simulation *)malloc(sizeof(t_simulation));
	ctx_simulation->number_of_philosophers = atoi(argv[1]);
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
	ctx_simulation->time_to_die = atoi(argv[2]);
	ctx_simulation->time_to_eat = atoi(argv[3]);
	ctx_simulation->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		ctx_simulation->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		ctx_simulation->number_of_times_each_philosopher_must_eat = -1;
	ctx_simulation->number_fill_eat = 0;
	//todo: errorcheck return 1
//	if (arg_error)
//		return (NULL);
	return (ctx_simulation);
}

int	main(int argc, char **argv)
{
	t_simulation	*ctx_simulation;

	if (argc == 5 || argc == 6)
	{
		ctx_simulation = init_philo(argc, argv);
		if (ctx_simulation == NULL)
			return (1);
		start_simulation(ctx_simulation);
	}
	return (0);
}