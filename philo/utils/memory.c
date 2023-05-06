/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:43 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/06 18:34:50 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all_at_last(t_simulation *ctx_simulation)
{
	(void)ctx_simulation;
	printf("終了！\n");
	exit(0);
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