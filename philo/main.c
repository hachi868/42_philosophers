/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:15:28 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/03 03:06:26 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static t_simulation	*init_philo(int argc, char **argv)
{
	t_simulation	*philosophers;
	int			i;

	i = 0;
	philosophers = (t_simulation *)malloc(sizeof(t_simulation));
	philosophers->number_of_philosophers = atoi(argv[1]);
	philosophers->philo_list = (t_philo_info **)malloc(\
		sizeof(t_philo_info *) * philosophers->number_of_philosophers);
	philosophers->folk_list = (pthread_mutex_t **)malloc(\
		sizeof(pthread_mutex_t *) * philosophers->number_of_philosophers);
	while (i < philosophers->number_of_philosophers)
	{
		philosophers->philo_list[i] = \
			(t_philo_info *)malloc(sizeof(t_philo_info));
		philosophers->folk_list[i] = \
			(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		i++;
	}
	philosophers->time_to_die = atoi(argv[2]);
	philosophers->time_to_eat = atoi(argv[3]);
	philosophers->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		philosophers->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		philosophers->number_of_times_each_philosopher_must_eat = -1;
	//todo: errorcheck return 1
//	if (arg_error)
//		return (NULL);
	return (philosophers);
}

int	main(int argc, char **argv)
{
	t_simulation	*philosophers;

	if (argc == 5 || argc == 6)
	{
		philosophers = init_philo(argc, argv);
		if (philosophers == NULL)
			return (1);
		start_simulation(philosophers);
	}
	return (0);
}