/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:52:57 by jurodrig          #+#    #+#             */
/*   Updated: 2026/02/28 20:19:56 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>

# define RST    "\033[0m"
# define RED    "\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

# define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	s_fork;
	int		fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex; // useful for races the monitor
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals; // [5] | FLAG if -1
	long		start_simulation;
	bool		end_simulation; // a philo dies or all philos full
	bool		all_threads_ready; // syncro philos
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex; // avoid races while reading from table
	t_mtx		write_mutex;
	t_fork		*forks; // array forks
	t_philo		*philos; // array philos
}				t_table;

// src

// *** utils ***
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

// *** synchro utils ***
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);

// *** write ***
void	write_status(t_philo_status status, t_philo *philo);

// *** parsing ***
void	parse_input(t_table *table, char **av);

// *** safe functions ***
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void	*data, t_opcode opcode);

//*** getters and setters ***
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest,
			long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);

//*** dinner ***
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);
void	*monitor_dinner(void *data);

//*** init ***
void	data_init(t_table *table);

#endif
