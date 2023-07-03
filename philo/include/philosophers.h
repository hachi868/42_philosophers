/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:14:52 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/04 02:45:54 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum s_status
{
	ENDED,
	NOT_ENDED
}	t_status;

typedef enum s_action
{
	TAKE_A_FORK,
	EAT,
	SLEEP,
	THINK
}	t_action;

typedef struct s_philo_info	t_philo_info;

typedef struct s_simulation
{
	t_philo_info	**philo_list;//哲学者全員
	pthread_mutex_t **folk_list; // フォークのmutex list
	int number_of_philosophers;	 // 哲学者人数
	int				time_to_die;//死ぬまでのリミット
	int				time_to_eat;//食事時間
	int				time_to_sleep;//睡眠時間
	long long		time_start;//開始時間(０リセット基準)
	int				number_of_times_each_philosopher_must_eat;//食べたら止まる場合の回数
	int				number_fill_eat;//食べきった哲学者の数
	pthread_mutex_t *mutex_fill_eat; // number_fill_eatのためのmutex
	bool			is_end;//終わりフラグ
	pthread_mutex_t *mutex_is_end; // is_endのためのmutex
}	t_simulation;

struct s_philo_info
{
	t_simulation	*ctx_simulation;//全部入り
	int				index;//哲学者ナンバリング 1からスタート（奇数は左きき、偶数は右利き）
	pthread_t		*thread;//哲学者はthreadである
	pthread_mutex_t	*spork;//スポーク（奇数なら右、偶数なら左）
	pthread_mutex_t *folk; // フォーク（奇数なら左、偶数なら右）
	bool			is_take_spork;//スポークを手にとっているか
	int				time_to_think;//食べるまでの思考時間
	long long		time_last_eaten;//最後に食べた時間
	int				count_eaten;// 食べた回数
};

// init_simulation.c
int			init_philo(t_simulation *ctx_simulation, int i);
int			start_simulation(t_simulation *ctx_simulation);

// state_change/eating.c
t_status	do_fork_and_eat(t_philo_info *philo);

// state_change/sleeping.c
t_status	do_sleep(t_philo_info *philo);

// state_change/thinking.c
t_status	do_think(t_philo_info *philo);

// state_change/died.c
void		check_living(t_simulation *ctx_simulation, t_philo_info *philo);
void		init_monitoring(t_philo_info *philo);
void		is_died(t_philo_info *philo);

// utils/ft_atoi_unsigned.c
int			free_args(int argc, int **ptr);
int			ft_atoi_unsigned(const char *str_num);

// utils/check_error.c
bool		is_invalid_args(int argc, char **argv, int *args);

// utils/get_time.c
long long	get_timestamp(void);
long long	get_timestamp_diff(t_simulation *ctx_simulation);
void		usleep_with_precision(t_simulation *ctx_simulation, long long sec_limit);

// utils/memory.c
void		free_all_at_last(t_simulation *ctx_simulation);
int			free_and_null(t_philo_info **ptr);
int			free_and_null2(pthread_mutex_t **ptr);

// utils/print.c
bool		check_end_and_print(t_philo_info *philo, t_action action);

#endif //PHILOSOPHERS_H
