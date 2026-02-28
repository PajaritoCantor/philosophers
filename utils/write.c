/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:35:55 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/28 23:08:04 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (!simulation_finished(philo->table) || status == DIED)
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
