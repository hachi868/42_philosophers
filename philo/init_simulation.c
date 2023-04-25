/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/26 02:29:29 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	repeat_print(int n, const char *func_name)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("%d: I'm philo %d : on %s\n", i, n, func_name);
		sleep(1);
		i++;
	}
}

// pthread_createの第3引数として渡す。
// voidポインタをreturnし、voidポインタの引数を1つ取る関数でないといけない。
// 引数はpthread_create第4引数から受け取れるが、今回は使わないのでNULLとなっている
void	*thread_func(void *arg)
{
	intptr_t	n;
	const char	*func_name;

	n = (intptr_t)arg;
	func_name = __func__;
	repeat_print(n + 2, func_name);
	printf("end: philo %ld\n", n);
	return ((void *)n);
}

int	start_simulation(t_simulation *philosophers)
{
	size_t		num_threads;
	pthread_t	*philo;
	size_t		i;

	num_threads = philosophers->number_of_philosophers;
	i = 0;
	philo = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
	while (i < num_threads)
	{
		if (pthread_create(&philo[i], NULL, thread_func, (void *)i) != 0)
		{
			printf("Error!スレッド作れなかった");
			//todo:free
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			printf("Error!スレッド待ち失敗");
			//todo:free
			return (1);
		}
		philo[i] = NULL;//pthread_joinはfreeされる？NULL埋めしておく
		i++;
	}
	printf("全スレッド終わり");
	return (0);
}
