/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:22 by harndt            #+#    #+#             */
/*   Updated: 2023/02/06 11:48:46 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initiates the program's configuration.
 * 
 * @param self A struct to store the program configuration.
 * @param argc The number of inputs given by command line.
 * @param argv The inputs given by command line.
 */
static void	init_config(t_config *self, int argc, char **argv)
{
	self->number_of_philosophers = ft_atoi(argv[0]);
	self->time_to_die = ft_atoi(argv[1]);
	self->time_to_eat = ft_atoi(argv[2]);
	self->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		self->times_must_eat = ft_atoi(argv[4]);
	else
		self->times_must_eat = 0;
	self->count_times_already_eaten = 0;
	self->start_time = ft_time();
	self->stop_print = FALSE;
	self->philo = malloc(sizeof(t_philo) * self->number_of_philosophers);
	if (!self->philo)
		return ;
	pthread_mutex_init(&self->mtx_death, NULL);
	pthread_mutex_init(&self->mtx_writer, NULL);
	pthread_mutex_init(&self->mtx_gameover, NULL);
	pthread_mutex_init(&self->mtx_stop_print, NULL);
	pthread_mutex_init(&self->mtx_current_time, NULL);
	pthread_mutex_init(&self->mtx_count_philos_already_eaten, NULL);
}

/**
 * @brief Initiates philosophers.
 * 
 * @param self Struct where the program's configuration are.
 */
static void	init_philos(t_config *self)
{
	int		count;
	t_philo	*philo;

	count = 0;
	while (count < self->number_of_philosophers)
	{
		philo = self->philo + count;
		philo->self = self;
		philo->id = count + 1;
		philo->times_eaten = 0;
		philo->start_time_eat = self->start_time;
		philo->thread_watchman = NULL;
		philo->mtx_fork_right = NULL;
		philo->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philo->thread)
			return ;
		pthread_mutex_init(&philo->mtx_times_eaten, NULL);
		pthread_mutex_init(&philo->mtx_fork_left, NULL);
		if (count == (self->number_of_philosophers - 1))
			philo->mtx_fork_right = &self->philo->mtx_fork_left;
		else
			philo->mtx_fork_right = &(philo + 1)->mtx_fork_left;
		count++;
	}
	printf("\n");
}

/**
 * @brief Checks the times eaten.
 * 
 * @param data Pointer to the configuration struct.
 * @return void* NULL
 */
static void	*times_eaten(void *data)
{
	t_config	*self;

	self = (t_config *)data;
	while (1)
	{
		pthread_mutex_lock(&self->mtx_count_philos_already_eaten);
		if (self->count_times_already_eaten == self->number_of_philosophers)
		{
			pthread_mutex_unlock(&self->mtx_count_philos_already_eaten);
			break ;
		}
		pthread_mutex_unlock(&self->mtx_count_philos_already_eaten);
	}
	printf("%d philosophers have eaten %d times(s)\n",
		self->number_of_philosophers, self->times_must_eat);
	pthread_mutex_unlock(&self->mtx_gameover);
	return (NULL);
}

/**
 * @brief Create philosophers as threads.
 * 
 * @param self A pointer to the config struct.
 */
static void	create_threads(t_config *self)
{
	int		count;
	t_philo	*philo;

	pthread_mutex_lock(&self->mtx_gameover);
	if (self->times_must_eat)
	{
		pthread_create(&self->times_eaten, NULL, &times_eaten, self);
		pthread_detach(self->times_eaten);
	}
	count = 0;
	while (count < self->number_of_philosophers)
	{
		philo = self->philo + count;
		if (pthread_create(philo->thread, NULL, &routine, philo) != 0)
			printf ("%s<ERROR>%s Philosophers Thread not created.\n",
				BRED, EOC);
		pthread_detach(*(philo->thread));
		count++;
	}
}

// argc[0] -- (char)	./philo
// argc[1] -- (int)		<number_of_philosopher>
// argc[2] -- (int)		<time_to_die>
// argc[3] -- (int)		<time_to_eat>
// argc[4] -- (int)		<time_to_sleep>
// argc[5] -- (int)		<number_of_times_each_philosopher_must_eat>
int	main(int argc, char *argv[])
{
	t_config	self;

	if (check_args(argc, argv))
	{
		init_config(&self, --argc, ++argv);
		init_philos(&self);
		create_threads(&self);
		pthread_mutex_lock(&self.mtx_gameover);
		ft_usleep(1000);
	}
	else
		return (1);
	return (0);
}
