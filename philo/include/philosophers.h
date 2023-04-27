/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:14:52 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/27 21:07:33 by hachi-gbg        ###   ########.fr       */
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

typedef struct s_simulation
{
	t_philo_info	*philo_head;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}	t_simulation;

typedef struct s_philo_info	t_philo_info;
struct s_philo_info
{
	int				index;
	pthread_t		*thread;
	pthread_mutex_t	spork;//odd
	pthread_mutex_t	folk;//even
	long long		time_last_eaten;
	int				count_eaten;
	t_philo_info	*next;
};

int			start_simulation(t_simulation *philosophers);

// state_change/take_a_folk.c
void		do_take_a_fork(t_philo_info *philo);

// state_change/eating.c
void		do_eat(t_philo_info *philo);

// state_change/sleeping.c
void		do_sleep(t_philo_info *philo);

// state_change/thinking.c
void		do_think(t_philo_info *philo);

// state_change/died.c
void		is_died(t_philo_info *philo);

// utils/atoi.c
int			ft_atoi_unsigned(char *str_num);

// utils/print.c
long long	get_timestamp(void);

#endif //PHILOSOPHERS_H
