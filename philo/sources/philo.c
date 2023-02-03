/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:22 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 11:53:21 by harndt           ###   ########.fr       */
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
	printf("[init_config]\tIniciando configurações\n");
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
	self->philo = malloc(sizeof(t_philo) * self->number_of_philosophers); //alocar memória para a quantidade de filosofes recebida
	if (!self->philo)
		return ;
	pthread_mutex_init(&self->mtx_death, NULL);
	pthread_mutex_init(&self->mtx_writer, NULL);
	pthread_mutex_init(&self->mtx_gameover, NULL);
	pthread_mutex_init(&self->mtx_stop_print, NULL);
	pthread_mutex_init(&self->mtx_current_time, NULL);
	pthread_mutex_init(&self->mtx_count_philos_already_eaten, NULL);
	printf("[init_config]\tConfigurações encerradas\n\n");
}

/**
 * @brief Initiates philosophers.
 * 
 * @param self Struct where the program's configuration are.
 */
static void	init_philos(t_config *self)
{
	int	count;
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
		printf("[init_philos]\tFilósofo |%d| criado.\n", count);
		count++;
	}
	printf("\n");
}

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
		printf("%ld %d %s\n", ft_time() - self->start_time, philo->id, logs[state]);
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
	printf("Filósofo #%d Comeu, Dormiu, Pensou\n", philo->id);
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
static void *routine_watch(void *data)
{
	t_config	*self;
	t_philo	*philo;
	
	philo = (t_philo *)data;
	self = philo->self;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx_times_eaten);
		if (self->times_must_eat && (philo->times_eaten >= self->times_must_eat))
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
	printf("Assistindo o filósofo #%d.\n", philo->id);
	return (NULL);
}

/**
 * @brief Defines the routine to a philosopher.
 * 
 * @param data Pointer to the configuration struct.
 * @return void* NULL
 */
static void	*routine(void *data)
{
	printf("[pthread_self]\tThread |%ld| criada\n", pthread_self());
	t_philo	*philo;
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
		if (self->times_must_eat && (philo->times_eaten == self->times_must_eat))
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
	printf("%d philosophers gave eate %d times(s)\n", self->number_of_philosophers, self->times_must_eat);
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
	int	count;
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
			printf ("<ERROR> Philosophers Thread not created.\n");
		printf("[create_threads]\tThread |%p| para o filosófo |%d| criada\n", philo->thread, count);
		pthread_detach(*(philo->thread));
		count++;
	}

	// comentar
	// printf("\n");
	// count = 0;
	// while (count < self->number_of_philosophers)
	// {
	// 	philo = self->philo + count;
	// 	if (pthread_join(*(philo->thread), NULL) != 0)
	// 		printf("Erro ao unir thread.\n");
	// 	printf("[join_threads]\tThread |%p| unida\n", philo->thread);
	// 	count++;
	// }
}

/**
 * @brief Prints the program's configuration.
 * 
 * @param self A pointer to the config struct.
 */
static void	print_config(t_config *self)
{
	printf("Total of philosophers:\t|%d|\n", self->number_of_philosophers);
	printf("Time to die\t\t|%d|\n", self->time_to_die);
	printf("Time to eat\t\t|%d|\n", self->time_to_eat);
	printf("Time to sleep\t\t|%d|\n", self->time_to_sleep);
	printf("Times to eat\t\t|%d|\n", self->times_must_eat);
}

/**
 * @brief Checks the received arguments and returns if the program can run.
 * 
 * @param argc Total arguments received by command line.
 * @param argv Argumentes received by command line.
 * @return t_bool TRUE if the program can run, otherwise FALSE.
 */
static t_bool	check_args(int argc, char **argv)
{
	int		count;

	if (argc != 5 && argc != 6) // checa se a quantidade adequada de parâmetros foi recebida
	{
		printf("<USAGE ERROR> Number of arguments invalid.\n");
		return (FALSE);
	} 
	count = 1;
	while (count < argc)
	{
		if (!ft_isnum(argv[count++])) // checar se parâmetros recebidos contém apenas números
		{
			printf("<USAGE ERROR> All argumetns must be int.\n");
			return (FALSE);
		}
	}
	if (argv[1])
	{
		if (ft_atoi(argv[1]) <= 0) // checa se o número de filósofos é maior que zero
		{
			printf("<USAGE ERROR> Number of philosophers must be greater than 0.\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

// argc[0] -- (char)	./philo
// argc[1] -- (int)		<number_of_philosopher>
// argc[2] -- (int)		<time_to_die>
// argc[3] -- (int)		<time_to_eat>
// argc[4] -- (int)		<time_to_sleep>
// argc[5] -- (int)		<number_of_times_each_philosopher_must_eat>
int main(int argc, char *argv[])
{
	t_config	self;

	if (check_args(argc, argv))
	{
		init_config(&self, --argc, ++argv);
		init_philos(&self);
		create_threads(&self);
		pthread_mutex_lock(&self.mtx_gameover);
		ft_usleep(1000);
		pthread_exit(NULL);
	}
	else
		return (1);
	return (0);
}
