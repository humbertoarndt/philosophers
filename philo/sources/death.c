/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:44:52 by harndt            #+#    #+#             */
/*   Updated: 2023/02/07 17:34:23 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_simulation_stop(t_config *self, t_bool status)
{
	pthread_mutex_lock(&self->simulation_stop_lock);
	self->stop_simulation = status;
	pthread_mutex_unlock(&self->simulation_stop_lock);
}

t_bool	has_simulation_stopped(t_config *self)
{
	t_bool	flag;

	flag = FALSE;
	pthread_mutex_lock(&self->simulation_stop_lock);
	if (self->stop_simulation == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(&self->simulation_stop_lock);
	return (flag);
}

static t_bool	kill_philosopher(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->self->time_to_die)
	{
		set_simulation_stop(philo->self, TRUE);
		write_status(philo, TRUE, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	end_condition_reached(t_config *self)
{
	unsigned int	i;
	t_bool			ate_enough;

	i = 0;
	ate_enough = TRUE;
	while (i < self->nb_philos)
	{
		pthread_mutex_lock(&self->philos[i]->meal_time_lock);
		if (kill_philosopher(self->philos[i]))
			return (TRUE);
		if (self->must_eat_count != -1)
			if (self->philos[i]->times_ate < (unsigned int)self->must_eat_count)
				ate_enough = FALSE;
		pthread_mutex_unlock(&self->philos[i]->meal_time_lock);
		i++;
	}
	if (self->must_eat_count != -1 && ate_enough == TRUE)
	{
		set_simulation_stop(self, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

void	*death(void *data)
{
	t_config	*self;

	self = (t_config *)data;
	if (self->must_eat_count == 0)
		return (NULL);
	set_simulation_stop(self, FALSE);
	simulation_start_delay(self->start_time);
	while (TRUE)
	{
		if (end_condition_reached(self) == TRUE)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
