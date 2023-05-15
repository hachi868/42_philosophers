/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:52:01 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/05/16 02:27:01 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi_unsigned(const char *str_num)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	while (str_num[i] == ' ' || (str_num[i] >= 9 && str_num[i] <= 13))
		i++;
	if (str_num[i] == '-')
		return (-1);
	else if (str_num[i] == '+')
		i++;
	if (!(str_num[i] >= '0' && str_num[i] <= '9'))
		return (-1);
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		num = num * 10 + (str_num[i] - '0');
		i++;
	}
	return (num);
}

//int	main(void)
//{
//	printf("%s => %d:%d\n", "1", atoi("1"), ft_atoi_unsigned("1"));
//	printf("%s => %d:%d\n", "a1", atoi("a1"), ft_atoi_unsigned("a1"));
//	printf("%s => %d:%d\n", "--1", atoi("--1"), ft_atoi_unsigned("--1"));
//	printf("%s => %d:%d\n", "++1", atoi("++1"), ft_atoi_unsigned("++1"));
//	printf("%s => %d:%d\n", "+1", atoi("+1"), ft_atoi_unsigned("+1"));
//	printf("%s => %d:%d\n", "-1", atoi("-1"), ft_atoi_unsigned("-1"));
//	printf("%s => %d:%d\n", "+0", atoi("+0"), ft_atoi_unsigned("+0"));
//	printf("%s => %d:%d\n", "-0", atoi("-0"), ft_atoi_unsigned("-0"));
//	printf("%s => %d:%d\n", "+", atoi("+"), ft_atoi_unsigned("+"));
//	printf("%s => %d:%d\n", "-", atoi("-"), ft_atoi_unsigned("-"));
//	printf("%s => %d:%d\n", "+42lyon", atoi("+42lyon"), ft_atoi_unsigned("+42lyon"));
//	printf("%s => %d:%d\n", "+101", atoi("+101"), ft_atoi_unsigned("+101"));
//  printf("%s => %d:%d\n",
//         "2147483647", atoi("2147483647"), ft_atoi_unsigned("2147483647"));
//  printf("%s => %d:%d\n",
//         "2147483648", atoi("2147483648"), ft_atoi_unsigned("2147483648"));
//	printf("%s => %d:%d\n",
//				 "-2147483648", atoi("-2147483648"), ft_atoi_unsigned("-2147483648"));
//	printf("%s => %d:%d\n", "-+42", atoi("-+42"), ft_atoi_unsigned("-+42"));
//	printf("%s => %d:%d\n", "+-42", atoi("+-42"), ft_atoi_unsigned("+-42"));
//	printf("%s => %d:%d\n", "+42", atoi("+42"), ft_atoi_unsigned("+42"));
//	printf("%s => %d:%d\n", "- 42", atoi("- 42"), ft_atoi_unsigned("- 42"));
//	printf("%s => %d:%d\n", "1 42", atoi("1 42"), ft_atoi_unsigned("1 42"));
//	printf("%s => %d:%d\n", "-1 42", atoi("-1 42"), ft_atoi_unsigned("-1 42"));
//	printf("%s => %d:%d\n", "-123",	atoi("-123"),	ft_atoi_unsigned("-123"));
//	printf("%s => %d:%d\n", "--123",	atoi("--123"),	ft_atoi_unsigned("--123"));
//	printf("%s => %d:%d\n", "123-",	atoi("   123"),	ft_atoi_unsigned("   123"));
//	printf("%s => %d:%d\n", "123-",	atoi("   123-"),	ft_atoi_unsigned("   123-"));
//	printf("%s => %d:%d\n", "12 3-",	atoi("   12 3-"),	ft_atoi_unsigned("   12 3-"));
//	printf("%s => %d:%d\n", "++123",	atoi("  ++123"),	ft_atoi_unsigned("  ++123"));
//	printf("%s => %d:%d\n", "-6.4c",	atoi("-6.4c"),	ft_atoi_unsigned("-6.4c"));
//	printf("%s => %d:%d\n", "+6.4c",	atoi("+6.4c"),	ft_atoi_unsigned("+6.4c"));
//	printf("%s => %d:%d\n", "-A",	atoi("-A"),	ft_atoi_unsigned("-A"));
//	return (0);
//}