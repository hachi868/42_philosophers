/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:52:01 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/07/08 22:22:57 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_strlen(const char *str_num)
{
	int	i;

	i = 0;
	while (str_num[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi_unsigned(const char *str_num)
{
	size_t		i;
	long long	num;

	i = 0;
	num = 0;
	while (str_num[i] == ' ' || (str_num[i] >= 9 && str_num[i] <= 13))
		i++;
	if (str_num[i] == '-')
	{
		if (str_num[i + 1] == '0' && str_num[i + 2] == '\0')
			i++;
		else
			return (-1);
	}
	else if (str_num[i] == '+')
		i++;
	if (!(str_num[i] >= '0' && str_num[i] <= '9') \
		|| ft_strlen(&str_num[i]) > 10)
		return (-1);
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		num = num * 10 + (str_num[i] - '0');
		i++;
	}
	if (num > INT_MAX || str_num[i] != '\0')
		return (-1);
	return ((int)num);
}
