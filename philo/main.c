/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:15:28 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 02:29:56 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static t_simulation	*init_philo(int argc, char **argv)
{
	t_simulation	*philosophers;

	philosophers = (t_simulation *)malloc(sizeof(t_simulation));
	philosophers->number_of_philosophers = atoi(argv[1]);
	philosophers->time_to_die = atoi(argv[2]);
	philosophers->time_to_eat = atoi(argv[3]);
	philosophers->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
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