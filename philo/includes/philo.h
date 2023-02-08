/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:11 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 13:58:56 by harndt           ###   ########.fr       */
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

# include "colors.h"

// =============================================================================
// MACROS
// =============================================================================

# define TRUE 1
# define FALSE 0
# define MAX_PHILOS 250
# define INT_MAX 2147483647
# define STR_MAX_PHILOS "250"
# define STR_PROG_NAME "philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_PHILO	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_MUTEX "%s error: Could not create mutex.\n"
# define STR_ERR_THREAD "%s error: Could not create thread.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"

// =============================================================================
// TYPEDEF / STRUCT 
// =============================================================================

/**
 * @brief Boolean type. TRUE (1)/FALSE (0)
 */
typedef int				t_bool;

/**
 * @brief Philosophers states.
 */
typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

typedef struct s_philo	t_philo;
typedef struct s_config	t_config;

/**
 * @brief ./philo configurations.
 */
typedef struct s_config
{
	pthread_t		death;
	t_philo			**philos;
	unsigned int	nb_philos;
	pthread_mutex_t	write_lock;
	time_t			start_time;
	pthread_mutex_t	*fork_locks;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	t_bool			stop_simulation;
	pthread_mutex_t	simulation_stop_lock;
}	t_config;

/**
 * @brief Philosopher's individual configuration.
 */
typedef struct s_philo
{
	unsigned int	id;
	t_config		*self;
	pthread_t		thread;
	unsigned int	fork[2];
	time_t			last_meal;
	unsigned int	times_ate;
	pthread_mutex_t	meal_time_lock;
}	t_philo;

// =============================================================================
// STRINGS FUNCTIONS
// =============================================================================

int			ft_atoi(char *str);
t_bool		is_valid_input(int argc, char *argv[]);

// =============================================================================
// INIT FUNCTIONS
// =============================================================================

t_config	*init_config(int argc, char *argv[]);

// =============================================================================
// EXIT FUNCTIONS
// =============================================================================

void		*free_config(t_config *self);
void		destroy_mutexes(t_config	*self);
int			msg(char *str, char *detail, int exit_nb);
void		*error_null(char *str, char *details, t_config *self);
int			error_failure(char *str, char *details, t_config *self);

// =============================================================================
// TIME FUNCTION
// =============================================================================

time_t		get_time_in_ms(void);
void		simulation_start_delay(time_t star_time);
void		philo_sleep(t_config *self, time_t sleep_time);

// =============================================================================
// OUTPUT FUNCTION
// =============================================================================

void		write_outcome(t_config *self);
void		write_status(t_philo *philo, t_bool obituary, t_status status);

// =============================================================================
// DEATH FUNCTION
// =============================================================================

void		*death(void *data);
t_bool		has_simulation_stopped(t_config *self);

// =============================================================================
// PHILO FUNCTIONS
// =============================================================================

void		*philo(void *data);

#endif