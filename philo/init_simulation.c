/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 10:57:59 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static int	init_fork_mutex_list(t_simulation *ctx_simulation, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		if (pthread_mutex_init(ctx_simulation->fork_list[i], NULL) != 0)
		{
			free_all_at_last(ctx_simulation);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philo_list(t_simulation *ctx_simulation, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		init_philo(ctx_simulation, i);
		i++;
	}
	return (0);
}

static int	join_philo_list(t_simulation *ctx_simulation, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(*ctx_simulation->philo_list[i]->thread, NULL) != 0)
		{
			printf("Error: start_simulation: "
				"Failed to create a new thread using pthread_join.\n");
			free_all_at_last(ctx_simulation);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_simulation *ctx_simulation)
{
	int	num_threads;

	num_threads = ctx_simulation->number_of_philosophers;
	init_fork_mutex_list(ctx_simulation, num_threads);
	ctx_simulation->time_start = get_timestamp();
	init_philo_list(ctx_simulation, num_threads);
	join_philo_list(ctx_simulation, num_threads);
	free_all_at_last(ctx_simulation);
	return (0);
}
