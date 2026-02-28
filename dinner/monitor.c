/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:43:12 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/28 23:15:47 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	last_meal;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	last_meal = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = gettime(MILLISECOND) - last_meal;
	if (elapsed > philo->table->time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		usleep(100);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
				return (NULL);
			}
		}
		usleep(200);
	}
	return (NULL);
}
