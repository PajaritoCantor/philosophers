/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:35:55 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/28 21:47:51 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_status(t_philo_status status, t_philo *philo)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
    if (get_bool(&philo->philo_mutex, &philo->full))
        return ;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    if (status == DIED)
    {
        printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
    }
    else if (!simulation_finished(philo->table))
    {
        if (status == EATING)
            printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
        else if (status == SLEEPING)
            printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
        else if (status == THINKING)
            printf(W "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
        else
            printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
    }
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
