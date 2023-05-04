/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/04 15:51:16 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all(t_philo_info *philo)
{
	(void)philo;
//	clear_philo(philo);
//	free(philo);
//	philo = NULL;
}

int	free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (0);
}

//void	clear_philo(t_simulation *ctx_simulation)
//{
//
//}