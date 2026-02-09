/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:34:29 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/09 16:05:21 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (*str == '+')
		++str;
	else if ()
}
static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
}

void    parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	
}