/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 15:56:10 by hachi-gbg        ###   ########.fr       */
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
void	*thread_func(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	pthread_mutex_lock(philo->spork);
	pthread_mutex_lock(philo->folk);
	printf("%zu: eating\n", philo->index);
	pthread_mutex_unlock(philo->folk);
	pthread_mutex_unlock(philo->spork);
	return ((void *)philo);
}

void	init_philo_info(t_simulation *ctx_simulation, int i)
{
	t_philo_info	*philo_info;
	int				num_philo;

	num_philo = ctx_simulation->number_of_philosophers;
	philo_info = ctx_simulation->philo_list[i];
	philo_info->index = i + 1;
	if (i % 2 == 0)
	{
		if (i == num_philo - 1)
			philo_info->spork = ctx_simulation->folk_list[0];
		else
			philo_info->spork = ctx_simulation->folk_list[i + 1];
		philo_info->folk = ctx_simulation->folk_list[i];
	}
	else
	{
		if (i == num_philo - 1)
			philo_info->folk = ctx_simulation->folk_list[0];
		else
			philo_info->folk = ctx_simulation->folk_list[i + 1];
		philo_info->spork = ctx_simulation->folk_list[i];
	}
	philo_info->time_last_eaten = 0;
	philo_info->count_eaten = 0;
	philo_info->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo_info->thread, NULL, thread_func, (void *)philo_info) != 0)
	{
		printf("Error!スレッド作れなかった");
		//todo:free
		return ;//error
	}
}

int	start_simulation(t_simulation *ctx_simulation)
{
	int	num_threads;
	int	i;

	num_threads = ctx_simulation->number_of_philosophers;
	i = 0;
	while (i < num_threads)
	{
		if (pthread_mutex_init(ctx_simulation->folk_list[i], NULL) != 0)
			exit(1);//todo:free
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		init_philo_info(ctx_simulation, i);
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(*ctx_simulation->philo_list[i]->thread, NULL) != 0)
		{
			printf("Error!スレッド待ち失敗");
			//todo:free
			return (1);
		}
		ctx_simulation->philo_list[i]->thread = NULL;//pthread_joinはfreeされる？NULL埋めしておく
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

//食事を開始したら、time_last_eatenに記録。time_to_die秒後に様子を見る。time_last_eatenとの差分で死んでるか判定。
//食事が終わったら食事回数++