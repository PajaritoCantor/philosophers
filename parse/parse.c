/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:34:29 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:46 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str)
{
	int	len;
	const char	*number;
	
	len = 0;
	while (is_space(*str))
		++str;
	if (*str == 43)
		++str;
	else if (*str == 45)
		error_exit("Feed me only positive valuse u suck!");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}
static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digt(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit!");
	return (num);
}

void    parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (table->time_to_die < 60
		|| table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		error_exit("use timestamps major than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
