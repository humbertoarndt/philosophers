/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:32:55 by harndt            #+#    #+#             */
/*   Updated: 2023/02/07 17:33:34 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->self->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, t_bool obituary, t_status status)
{
	pthread_mutex_lock(&philo->self->write_lock);
	if (has_simulation_stopped(philo->self) == TRUE && obituary == FALSE)
	{
		pthread_mutex_unlock(&philo->self->write_lock);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->self->write_lock);
}

void	write_outcome(t_config *self)
{
	unsigned int	i;
	unsigned int	full_count;

	i = 0;
	full_count = 0;
	while (i < self->nb_philos)
	{
		if (self->philos[i]->times_ate >= (unsigned int)self->must_eat_count)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&self->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n", full_count,
		self->nb_philos, self->must_eat_count);
	pthread_mutex_unlock(&self->write_lock);
	return ;
}
