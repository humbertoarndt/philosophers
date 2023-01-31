/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:11 by harndt            #+#    #+#             */
/*   Updated: 2023/01/30 17:10:15 by harndt           ###   ########.fr       */
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
# include <sys/time.h>	// gettimeofday

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
typedef enum	e_state
{
	EAT = 0,
	SLEEP = 1,
	THINK = 2
}	t_state;

typedef struct	s_philo t_philo;
typedef struct	s_config t_config;

/**
 * @brief ./philo configurations.
 */
typedef struct	s_config
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
	int	count_times_already_eaten;
	long	start_time;
	t_philo	*philo;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_gameover;
	pthread_mutex_t	mtx_current_time;
	pthread_mutex_t	mtx_count_philos_already_eaten;
}	t_config;

/**
 * @brief Philosopher's individual configuration.
 */
typedef struct	s_philo
{
	int			id;
	t_config	*self;
	int			times_eaten;
	long		start_time_eat;
	pthread_t	*thread;
	pthread_t	*thread_watchman;
	pthread_mutex_t	mtx_fork_left;
	pthread_mutex_t	mtx_fork_right;
	pthread_mutex_t	mtx_times_eaten;
}	t_philo;

#endif