/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:32:55 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 14:15:35 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints a plain text status message for a philospher as required by
 * the subject.
 * 
 * @param philo A pointer to the pihlosopher.
 * @param str The message to be printed.
 */
static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->self->start_time,
		philo->id + 1, str);
}

/**
 * @brief Prints the status of a philosopher as long as the simluation still
 * active.
 * 
 * @param philo A pointer to the pihlosopher.
 * @param obituary Status received by the death routine.
 * @param status Current philosopher status.
 */
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
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->self->write_lock);
}

/**
 * @brief Prints the outcome of the simulation when a number of times to eat
 * is given by command line.
 * 
 * @param self A pointer to the programs config structure.
 */
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
