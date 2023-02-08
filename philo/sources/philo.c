/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:59:16 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 13:48:31 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Locks the forks for a philosopher and let him eat, then put heim to
 * sleep.
 * 
 * @param philo A pointer to the philosopher structure.
 */
static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->self->fork_locks[philo->fork[0]]);
	write_status(philo, FALSE, GOT_FORK_1);
	pthread_mutex_lock(&philo->self->fork_locks[philo->fork[1]]);
	write_status(philo, FALSE, GOT_FORK_2);
	write_status(philo, FALSE, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->self, philo->self->time_to_eat);
	if (has_simulation_stopped(philo->self) == FALSE)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, FALSE, SLEEPING);
	pthread_mutex_unlock(&philo->self->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->self->fork_locks[philo->fork[0]]);
	philo_sleep(philo->self, philo->self->time_to_sleep);
}

/**
 * @brief Puts a philosopher to think. Calculates the time_to_think depending
 * on how long was his last meal, and determines when the philosophers needs
 * to eat again.
 * 
 * @param philo A pointer to the philosopher structure.
 * @param silent When TRUE the the philosophers is busy not talking;, else
 * the philosopher is thinking.
 */
static void	think_routine(t_philo *philo, t_bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->self->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->self->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == TRUE)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == FALSE)
		write_status(philo, FALSE, THINKING);
	philo_sleep(philo->self, time_to_think);
}

/**
 * @brief Routine used when only one philosophers is created. Since only one
 * fork exists, the philosophers must grab the forks and wait until his death.
 * 
 * @param philo A pointer to the philosopher structure.
 * @return void* A NULL pointer.
 */
static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->self->fork_locks[philo->fork[0]]);
	write_status(philo, FALSE, GOT_FORK_1);
	philo_sleep(philo->self, philo->self->time_to_die);
	write_status(philo, FALSE, DIED);
	pthread_mutex_unlock(&philo->self->fork_locks[philo->fork[0]]);
	return (NULL);
}

/**
 * @brief The philosopher thread routine.
 * 
 * @param data A pointer to the philosopher structure.
 * @return void* A NULL pointer.
 */
void	*philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->self->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->self->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	simulation_start_delay(philo->self->start_time);
	if (philo->self->time_to_die == 0)
		return (NULL);
	if (philo->self->nb_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, TRUE);
	while (has_simulation_stopped(philo->self) == FALSE)
	{
		eat_sleep_routine(philo);
		think_routine(philo, FALSE);
	}
	return (NULL);
}
