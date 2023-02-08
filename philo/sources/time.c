/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:44 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 12:54:47 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current time in miliseconds since the EPOCH
 * (1970-01-01 00:00:00)
 * 
 * @return time_t The time value in miliseconds.
 */
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Puts the philosopher to sleep, checks periodically if
 * it is time to wake up.
 * 
 * @param self A pointer to the programs config structure.
 * @param sleep_time How long the pilosopher should sleeps in miliseconds.
 */
void	philo_sleep(t_config *self, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(self))
			break ;
		usleep(100);
	}
}

/**
 * @brief Waits for a delay at the beginning of each thread.
 * 
 * @param star_time The starting time in miliseconds.
 */
void	simulation_start_delay(time_t star_time)
{
	while (get_time_in_ms() < star_time)
		continue ;
}
