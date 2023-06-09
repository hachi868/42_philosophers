/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:14:52 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/06 16:44:03 by hachi-gbg        ###   ########.fr       */
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

# define UNLOCK 0
# define LOCK 1

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
	int				number_of_philosophers;
	t_philo_info	**philo_list;
	pthread_mutex_t	**fork_list;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		time_start;
	int				number_of_times_each_philosopher_must_eat;
	int				number_fill_eat;
	pthread_mutex_t	*mutex_fill_eat;
	bool			is_end;
	pthread_mutex_t	*mutex_is_end;
}	t_simulation;

struct s_philo_info
{
	t_simulation	*ctx_simulation;
	int				index;
	pthread_t		*thread;
	int				spork;
	int				fork;
	int				time_to_think;
	long long		time_last_eaten;
	int				count_eaten;
};

// init_simulation.c
int			start_simulation(t_simulation *ctx_simulation);

// init_philo.c
int			init_philo(t_simulation *ctx_simulation, int i);

// state_change/eating01.c
t_status	do_fork_and_eat(t_philo_info *philo);

// state_change/eating02.c
t_status	do_take_a_fork(t_philo_info *philo);
t_status	do_eat(t_philo_info *philo);
void		is_fill_eat(\
	t_simulation *ctx_simulation, t_philo_info *philo);
bool		check_each_eaten(t_philo_info *philo);

// state_change/sleeping.c
t_status	do_sleep(t_philo_info *philo);

// state_change/thinking.c
t_status	do_think(t_philo_info *philo);

// state_change/died.c
void		check_living(t_simulation *ctx_simulation, t_philo_info *philo);
void		init_monitoring(t_philo_info *philo);

// utils/ft_atoi_unsigned.c
int			free_args(int argc, int *args);
int			ft_atoi_unsigned(const char *str_num);

// utils/check_error.c
bool		is_invalid_args(int argc, char **argv, int *args);

// utils/get_time.c
long long	get_timestamp(void);
long long	get_timestamp_diff(t_simulation *ctx_simulation);
void		usleep_with_precision(\
	t_simulation *ctx_simulation, long long sec_limit);

// utils/memory.c
void		free_ctx_simulation(t_simulation *ctx_simulation);
void		free_all_at_last(t_simulation *ctx_simulation);
void		free_and_null(void **ptr);

// utils/print.c
bool		check_end_and_print(t_philo_info *philo, t_action action);

// utils/ft_mutex.c
int			unlock_mutex_all(t_simulation *ctx_simulation);
#endif //PHILOSOPHERS_H
