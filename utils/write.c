/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:35:55 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/25 22:55:53 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* [timee_ms] [philo_id] [action]
*
* thread safe
* write mutex
*/
void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long	elapsed;

	elapsed = gettime(MILLISECOND);
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_sECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has take a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is eating\n", elapsed, philo->id);
		else if
    }
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}


