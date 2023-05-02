/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/03 02:45:35 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

//void	repeat_print(int n, const char *func_name)
//{
//	int	i;
//
//	i = 0;
//	while (i < n)
//	{
//		printf("%d: I'm philo %d : on %s\n", i, n, func_name);
//		i++;
//	}
//}

// pthread_createの第3引数として渡す。
// voidポインタをreturnし、voidポインタの引数を1つ取る関数でないといけない。
// 引数はpthread_create第4引数から受け取れるが、今回は使わないのでNULLとなっている
void	*thread_func(void *arg)
{
	intptr_t	n;
	//const char	*func_name;

	n = (intptr_t)arg;
	//func_name = __func__;
	//repeat_print(n, func_name);
	printf("thread_func: philo %ld\n", n);
	return ((void *)n);
}

void	init_philo_info(\
	t_philo_info *philo_info, size_t i, pthread_mutex_t	*list_folk)
{
	philo_info->index = i + 1;
	philo_info->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo_info->thread, NULL, thread_func, (void *)philo_info->index) != 0)
	{
		printf("Error!スレッド作れなかった");
		//todo:free
		return ;//error
	}
	if (i % 2)//todo:ラストは0に。
	{
		philo_info->spork = list_folk[i];
		philo_info->folk = list_folk[i];
	}
	else
	{
		philo_info->spork = list_folk[i];
		philo_info->folk = list_folk[i];
	}
	philo_info->time_last_eaten = 0;
	philo_info->count_eaten = 0;
}

int	start_simulation(t_simulation *philosophers)
{
	size_t			num_threads;
	t_philo_info	*philo;
	pthread_mutex_t	*list_folk;
	size_t			i;

	num_threads = philosophers->number_of_philosophers;
	i = 0;
	philo = (t_philo_info *)malloc(sizeof(t_philo_info) * num_threads);
	list_folk = (pthread_mutex_t *)malloc(\
	sizeof(pthread_mutex_t) * num_threads);
	while (i < num_threads)
	{
		printf("start_simulation 1 - %zu\n", i);
		if (pthread_mutex_init(&list_folk[i], NULL) != 0)
			exit(1);//todo:free
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		printf("start_simulation 2 - %zu\n", i);
		init_philo_info(&philo[i], i, list_folk);//todo: 失敗した場合？
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(*philo[i].thread, NULL) != 0)
		{
			printf("Error!スレッド待ち失敗");
			//todo:free
			return (1);
		}
		philo[i].thread = NULL;//pthread_joinはfreeされる？NULL埋めしておく
		i++;
	}
	printf("全スレッド終わり");
	return (0);
}
//右利きと左利きが交互に座っている
//フォークを2本take
//食べる
//フォークを置く
//寝る
//思考
//まず先割れスプーンをとる。
// フォークが空いてたら取る。
//取れなかったら一旦置く