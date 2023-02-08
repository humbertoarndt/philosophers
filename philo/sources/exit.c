/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:05:55 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 12:31:29 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Frees all allocated memory by the program.
 * 
 * @param self A pointer to the programs config structure.
 * @return void* A NULL pointer.
 */
void	*free_config(t_config *self)
{
	unsigned int	i;

	if (!self)
		return (NULL);
	if (self->fork_locks != NULL)
		free(self->fork_locks);
	if (self->philos != NULL)
	{
		i = 0;
		while (i < self->nb_philos)
		{
			if (self->philos[i] != NULL)
				free(self->philos[i]);
			i++;
		}
		free(self->philos);
	}
	free(self);
	return (NULL);
}

/**
 * @brief Destroys every mutex created by the program
 * 
 * @param self A pointer to the programs config structure.
 */
void	destroy_mutexes(t_config *self)
{
	unsigned int	i;

	i = 0;
	while (i < self->nb_philos)
	{
		pthread_mutex_destroy(&self->fork_locks[i]);
		pthread_mutex_destroy(&self->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&self->write_lock);
	pthread_mutex_destroy(&self->simulation_stop_lock);
}

/**
 * @brief Prints a message on the terminal and return an exit code.
 * 
 * @param str The error ocurred.
 * @param detail Any relevant error details.
 * @param exit_nb The error exit code.
 * @return int The error exit code.
 */
int	msg(char *str, char *detail, int exit_nb)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_nb);
}

/**
 * @brief Prints a message on the terminal and frees all memory.
 * 
 * @param str The error ocurred.
 * @param detail Any relevant error details.
 * @param self A pointer to the programs config structure.
 * @return int 0 to indicate failure.
 */
int	error_failure(char *str, char *details, t_config *self)
{
	if (self != NULL)
		free_config(self);
	return (msg(str, details, 0));
}

/**
 * @brief Prints a message on the terminal and frees all memory.
 * 
 * @param str The error ocurred.
 * @param detail Any relevant error details.
 * @param self A pointer to the programs config structure.
 * @return void* A NULL pointer.
 */
void	*error_null(char *str, char *details, t_config *self)
{
	if (self != NULL)
		free_config(self);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}
