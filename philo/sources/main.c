/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:35:56 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 12:58:28 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Launches the simulation, creates all philosophers threas and a
 * controller thread, death, to check when a philosopher dies.
 * 
 * @param self A pointer to the programs config structure.
 * @return t_bool In case of success return TRUE, else FALSE.
 */
static t_bool	start_simulation(t_config *self)
{
	unsigned int	i;

	self->start_time = get_time_in_ms() + (self->nb_philos * 2 * 10);
	i = 0;
	while (i < self->nb_philos)
	{
		if (pthread_create(&self->philos[i]->thread, NULL, &philo,
				self->philos[i]) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, self));
		i++;
	}
	if (self->nb_philos > 1)
	{
		if (pthread_create(&self->death, NULL, &death, self) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, self));
	}
	return (TRUE);
}

/**
 * @brief Stops the philosophers simulation. Unite the all threads using join,
 * destroy all mutexes and frees all allocated memory.
 * 
 * @param self A pointer to the programs config structure.
 */
static void	stop_simulation(t_config *self)
{
	unsigned int	i;

	i = 0;
	while (i < self->nb_philos)
	{
		pthread_join(self->philos[i]->thread, NULL);
		i++;
	}
	if (self->nb_philos > 1)
		pthread_join(self->death, NULL);
	destroy_mutexes(self);
	free_config(self);
}

/**
 * @brief Main function, checks args received by command line and executes
 * the program.
 * 
 * @param argc Total number of args received by command line.
 * @param argv Args received by command line.
 * @return int On success returns 0, else returns 1.
 */
int	main(int argc, char *argv[])
{
	t_config	*self;

	self = NULL;
	if (argc != 5 && argc != 6)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	self = init_config(--argc, ++argv);
	if (!self)
		return (EXIT_FAILURE);
	if (!start_simulation(self))
		return (EXIT_FAILURE);
	stop_simulation(self);
	return (EXIT_SUCCESS);
}
