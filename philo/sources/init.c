/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:18:34 by harndt            #+#    #+#             */
/*   Updated: 2023/02/07 17:36:43 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_config *self)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * self->nb_philos);
	if (!forks)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < self->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->self->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->self->nb_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philos(t_config *self)
{
	unsigned int	i;
	t_philo			**philos;

	philos = malloc(sizeof(t_philo) * self->nb_philos);
	if (!philos)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < self->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null(STR_ERR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		philos[i]->self = self;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static t_bool	init_global_mtx(t_config *self)
{
	self->fork_locks = init_forks(self);
	if (!self->fork_locks)
		return (FALSE);
	if (pthread_mutex_init(&self->simulation_stop_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, self));
	if (pthread_mutex_init(&self->write_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, self));
	return (TRUE);
}

t_config	*init_config(int argc, char *argv[])
{
	t_config	*self;

	self = malloc(sizeof(t_config) * 1);
	if (!self)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	self->nb_philos = integer_atoi(argv[0]);
	self->time_to_die = integer_atoi(argv[1]);
	self->time_to_eat = integer_atoi(argv[2]);
	self->time_to_sleep = integer_atoi(argv[3]);
	if (argc == 5)
		self->must_eat_count = integer_atoi(argv[4]);
	else
		self->must_eat_count = -1;
	self->philos = init_philos(self);
	if (!self->philos)
		return (NULL);
	if (!init_global_mtx(self))
		return (NULL);
	self->stop_simulation = FALSE;
	return (self);
}
