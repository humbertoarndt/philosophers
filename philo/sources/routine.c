/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:32:36 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 16:26:37 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints a status log.
 * 
 * @param philo Pointer to a Philosopher.
 * @param state e_num states.
 */
static void	change_status(t_philo *philo, t_state state)
{
	t_config	*self;
	static char	*logs[5] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
	};

	self = philo->self;
	pthread_mutex_lock(&self->mtx_writer);
	pthread_mutex_lock(&self->mtx_stop_print);
	if (!self->stop_print)
		printf("%ld %d %s\n",
			ft_time() - self->start_time, philo->id, logs[state]);
	pthread_mutex_unlock(&self->mtx_stop_print);
	pthread_mutex_unlock(&self->mtx_writer);
}

/**
 * @brief Handles variables to a multithread program.
 * 
 * @param self Pointer to the configuration struct.
 * @param philo Pointer to a philosopher.
 */
static void	eat_sleep_think(t_config *self, t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_fork_left);
	change_status(philo, FORK);
	pthread_mutex_lock(philo->mtx_fork_right);
	change_status(philo, FORK);
	change_status(philo, EAT);
	pthread_mutex_lock(&self->mtx_current_time);
	philo->start_time_eat = ft_time();
	pthread_mutex_unlock(&self->mtx_current_time);
	ft_usleep(self->time_to_eat);
	pthread_mutex_lock(&philo->mtx_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->mtx_times_eaten);
	pthread_mutex_unlock(&philo->mtx_fork_left);
	pthread_mutex_unlock(philo->mtx_fork_right);
	change_status(philo, SLEEP);
	ft_usleep(self->time_to_sleep);
	change_status(philo, THINK);
}

/**
 * @brief Kills a philosopher.
 * 
 * @param self Pointer to the configuration struct.
 * @param philo Pointer to a philosopher.
 */
static void	kill_philo(t_config *self, t_philo *philo)
{
	pthread_mutex_unlock(&self->mtx_current_time);
	pthread_mutex_lock(&self->mtx_death);
	pthread_mutex_lock(&self->mtx_stop_print);
	self->stop_print = TRUE;
	pthread_mutex_unlock(&self->mtx_stop_print);
	pthread_mutex_lock(&self->mtx_writer);
	printf("%ld %d died\n", ft_time() - self->start_time, philo->id);
	pthread_mutex_unlock(&self->mtx_gameover);
	pthread_detach(*philo->thread_watchman);
	pthread_detach(*philo->thread);
}

/**
 * @brief Defines a routine to watch a philosophers
 * 
 * @param data Pointer to a philosopher.
 * @return void* NULL
 */
static void	*routine_watch(void *data)
{
	t_philo		*philo;
	t_config	*self;

	philo = (t_philo *)data;
	self = philo->self;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx_times_eaten);
		if (self->times_must_eat
			&& (philo->times_eaten >= self->times_must_eat))
		{
			pthread_mutex_unlock(&philo->mtx_times_eaten);
			pthread_detach(*philo->thread);
			pthread_detach(*philo->thread_watchman);
			break ;
		}
		pthread_mutex_unlock(&philo->mtx_times_eaten);
		pthread_mutex_lock(&self->mtx_current_time);
		if (philo->start_time_eat + self->time_to_die <= ft_time())
			kill_philo(self, philo);
		pthread_mutex_unlock(&self->mtx_current_time);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo		*philo;
	t_config	*self;
	pthread_t	watchman;

	philo = (t_philo *)data;
	self = philo->self;
	if (philo->id % 2)
		ft_usleep(self->time_to_eat / 10);
	philo->thread_watchman = &watchman;
	if (pthread_create(&watchman, NULL, &routine_watch, philo) != 0)
		printf("<ERROR> Watchman Thread not created.\n");
	while (1)
	{
		if (self->times_must_eat
			&& (philo->times_eaten == self->times_must_eat))
		{
			pthread_mutex_lock(&self->mtx_count_philos_already_eaten);
			self->count_times_already_eaten++;
			pthread_mutex_unlock(&self->mtx_count_philos_already_eaten);
			break ;
		}
		eat_sleep_think(self, philo);
	}
	return (NULL);
}
