/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 03:29:52 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 12:04:16 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static void	*thread_func(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	if (philo->index % 2 == 0)
		usleep(5);
	if (philo->index == philo->ctx_simulation->number_of_philosophers)
		usleep(philo->ctx_simulation->time_to_eat);
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

static int	init_philo_info(\
	t_philo_info *philo_info, int num_philo, \
	t_simulation *ctx_simulation, int i)
{
	(void)num_philo;
	philo_info->ctx_simulation = ctx_simulation;
	philo_info->index = i + 1;
	assign_fork(philo_info, i);
	philo_info->time_last_eaten = 0;
	philo_info->count_eaten = 0;
	if (num_philo % 2 == 1)
		philo_info->time_to_think = 5;
	return (0);
}

int	init_philo(t_simulation *ctx_simulation, int i)
{
	t_philo_info	*philo_info;
	int				num_philo;

	num_philo = ctx_simulation->number_of_philosophers;
	philo_info = ctx_simulation->philo_list[i];
	init_philo_info(philo_info, num_philo, ctx_simulation, i);
	philo_info->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo_info->thread, NULL, thread_func, (void *)philo_info) != 0)
	{
		printf("Error: init_philo: "
			"Failed to create a new thread using pthread_create.\n");
		free_all_at_last(ctx_simulation);
		return (1);
	}
	init_monitoring(philo_info);
	return (0);
}
