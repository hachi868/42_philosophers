/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/23 23:39:53 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

int	start_simulation(t_philo *philosophers)
{
	pthread_t	**philo;
	size_t		counter;

	counter = philosophers->number_of_philosophers;
	philo = (pthread_t **)malloc(sizeof(pthread_t *) * counter);
	while (counter > 0)
	{
		pthread_create(&thread1, NULL, thread_func, (void *)100000);
		pthread_join(thread1, NULL);
		counter--;
	}
	return (0);
}