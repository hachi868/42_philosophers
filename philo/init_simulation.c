/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:27:40 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/03 17:45:28 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

static void	*thread_func(void *arg)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)arg;
	if (philo->ctx_simulation->number_of_philosophers % 2 == 1)//奇数なら調整いれる
	{
		if (philo->index == 1)
			usleep(200);
		else if (philo->index % 2 == 0)
			usleep(100);
	}
	// 順に実行
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

//それぞれの哲学者init
void	init_philo(t_simulation *ctx_simulation, int i)
{
	t_philo_info	*philo_info;
	int				num_philo;

	num_philo = ctx_simulation->number_of_philosophers;
	philo_info = ctx_simulation->philo_list[i];
	philo_info->ctx_simulation = ctx_simulation;
	philo_info->index = i + 1;
	//fork割り当て
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
	// 最後に食べた時間を開始時で初期化
	philo_info->time_last_eaten = ctx_simulation->time_start;
	philo_info->count_eaten = 0;
	if (num_philo % 2 == 1 && i % 5 < 3)//不明？？哲学者の人数が奇数、もう一つは？
		philo_info->time_to_think = ctx_simulation->time_to_eat;
	else
		philo_info->time_to_think = 0;
	philo_info->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (pthread_create(\
		philo_info->thread, NULL, thread_func, (void *)philo_info) != 0)
	{
		printf("Error!スレッド作れなかった init_philo_info\n");
		//todo:free
		return ;//error
	}
	init_monitoring(philo_info);
}

int	start_simulation(t_simulation *ctx_simulation)
{
	int	num_threads;
	int	i;

	num_threads = ctx_simulation->number_of_philosophers;//哲学者の数 = フォークの数
	i = 0;
	// フォークのmutexは全てを作ってしまう。哲学者に割り当てるため
	while (i < num_threads)
	{
		if (pthread_mutex_init(ctx_simulation->folk_list[i], NULL) != 0)
			exit(1);//todo:free
		i++;
	}
	//開始時間 定義
	ctx_simulation->time_start = get_timestamp();
	// 哲学者 init
	i = 0;
	while (i < num_threads)
	{
		init_philo(ctx_simulation, i);
		i++;
	}
	//終わり待ち
	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(*ctx_simulation->philo_list[i]->thread, NULL) != 0)
		{
			printf("Error!スレッド待ち失敗");
			//todo:free
			return (1);
		}
		ctx_simulation->philo_list[i]->thread = NULL;
		i++;
	}
	free_all_at_last(ctx_simulation);
	return (0);
}
