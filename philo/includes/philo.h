/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:11 by harndt            #+#    #+#             */
/*   Updated: 2023/01/23 16:11:38 by harndt           ###   ########.fr       */
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
	EAT,
	SLEEP,
	THINK
}	t_state;

typedef struct	s_config t_config;
typedef struct	s_philo t_philo;

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
	t_philo	*philo;
}	t_config;

/**
 * @brief Philosopher's individual configuration.
 */
typedef struct	s_philo
{
	int			id;
	t_config	*self;
}	t_philo;

#endif