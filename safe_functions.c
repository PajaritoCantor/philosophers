/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:08:12 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/17 02:09:09 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Containing wrapper functions
* with embedded controls on return
*/

void	*safe_malloc(size_t bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return(ret);
}

// *** MUTEX SAFE ***
/*
 * lock
 * unlock
 * init
 * destroy
 * create
 * join
 * detach
*/

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == opcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(mutex);
}