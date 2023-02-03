/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:11 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 16:15:24 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// =============================================================================
// LOCAL LIBRARIES
// =============================================================================

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <pthread.h>	// pthread functions

// =============================================================================
// PERSONAL LIBRARIES
// =============================================================================

# include "utils.h"
# include "colors.h"

// =============================================================================
// STRUCTS
// =============================================================================

/**
 * @brief Philosophers states.
 */
typedef enum e_state
{
	EAT,
	FORK,
	SLEEP,
	THINK
}	t_state;

typedef struct s_philo	t_philo;
typedef struct s_config	t_config;

/**
 * @brief ./philo configurations.
 */
typedef struct s_config
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				number_of_philosophers;
	int				count_times_already_eaten;
	long			start_time;
	t_bool			stop_print;
	t_philo			*philo;
	pthread_t		times_eaten;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_writer;
	pthread_mutex_t	mtx_gameover;
	pthread_mutex_t	mtx_stop_print;
	pthread_mutex_t	mtx_current_time;
	pthread_mutex_t	mtx_count_philos_already_eaten;
}	t_config;

/**
 * @brief Philosopher's individual configuration.
 */
typedef struct s_philo
{
	int				id;
	t_config		*self;
	int				times_eaten;
	long			start_time_eat;
	pthread_t		*thread;
	pthread_t		*thread_watchman;
	pthread_mutex_t	mtx_fork_left;
	pthread_mutex_t	*mtx_fork_right;
	pthread_mutex_t	mtx_times_eaten;
}	t_philo;

// =============================================================================
// FUNCTIONS
// =============================================================================

/**
 * @brief Defines the routine to a philosopher.
 * 
 * @param data Pointer to the configuration struct.
 * @return void* NULL
 */
void	*routine(void *data);

/**
 * @brief Checks the received arguments and returns if the program can run.
 * 
 * @param argc Total arguments received by command line.
 * @param argv Argumentes received by command line.
 * @return t_bool TRUE if the program can run, otherwise FALSE.
 */
t_bool	check_args(int argc, char **argv);

#endif