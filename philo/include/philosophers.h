/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:14:52 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/07 02:32:00 by hachi-gbg        ###   ########.fr       */
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

typedef struct s_philo_info	t_philo_info;

typedef struct s_simulation
{
	t_philo_info	**philo_list;
	pthread_mutex_t	**folk_list;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
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
	pthread_mutex_t	*spork;
	pthread_mutex_t	*folk;
	long long		time_last_eaten;
	int				count_eaten;
};

// init_simulation.c
void		init_philo(t_simulation *ctx_simulation, int i);
int			start_simulation(t_simulation *ctx_simulation);

// state_change/eating.c
int			do_eat(t_simulation *ctx_simulation, t_philo_info *philo);

// state_change/sleeping.c
int			do_sleep(t_simulation *ctx_simulation, t_philo_info *philo);

// state_change/thinking.c
int			do_think(t_philo_info *philo);

// state_change/died.c
void		check_living(t_philo_info *philo);
void		init_monitoring(t_philo_info *philo);
void		is_died(t_philo_info *philo);

// utils/atoi.c
int			ft_atoi_unsigned(char *str_num);

// utils/print.c
long long	get_timestamp(void);

// utils/memory.c
void		free_all_at_last(t_simulation *ctx_simulation);
int			free_and_null(void **ptr);

// utils/check_end.c
bool		check_end(t_simulation *ctx_simulation);

#endif //PHILOSOPHERS_H
