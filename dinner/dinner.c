/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:04:18 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/25 22:35:41 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* 0) wait all philos, synchro start
*
* 1) endless loop philo
*/
void	*dinner_simulation(voidi *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->tab);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		else if (philo->)
	}
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		;
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation
					&table->philos[i], CREATE);
	}
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL);
	// if we manage to reach this line, all philos are FULL!
	
}
