/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:22 by harndt            #+#    #+#             */
/*   Updated: 2023/01/31 13:21:11 by harndt           ###   ########.fr       */
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
	// self->start_time = pegar o tempo do começo
	self->philo = malloc(sizeof(t_philo) * self->number_of_philosophers); //alocar memória para a quantidade de filosofes recebida
	if (!self->philo)
		return ;
	pthread_mutex_init(&self->mtx_gameover, NULL);
	pthread_mutex_init(&self->mtx_current_time, NULL);
	pthread_mutex_init(&self->mtx_count_philos_already_eaten, NULL);
	printf("[init_config]\tConfigurações encerradas\n\n");
}

/**
 * @brief Gives birth to philosphers.
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
		// philo->start_time_eat = pegar tempo da struct config
		philo->thread = (pthread_t *)malloc(sizeof(pthread_t)); //alocar memória para 1 filosofo
		if (!philo->thread)
			return ;
		printf("[init_philos]\tFilósofo |%d| criado.\n", count);
		count++;
	}
	printf("\n");
}

static void	eat_sleep_think(t_philo *philo)
{
	printf("Filósofo #%d Comeu, Dormiu, Pensou\n", philo->id);
}

static void *routine_watch(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	printf("Assistindo o filósofo #%d.\n", philo->id);
}

static void	*routine(void *data)
{
	printf("[pthread_self]\tThread |%ld| criada\n", pthread_self());
	t_philo	*philo;
	t_config	*self;
	pthread_t	watchman;

	philo = (t_philo *)data;
	self = philo->self;
	philo->thread_watchman = &watchman;
	if (pthread_create(&watchman, NULL, &routine_watch, philo) != 0)
		printf("Erro ao criar vigia.\n");
	// while (1)
	for (int i = 0; i < 5; i++)
	{
		if (self->times_must_eat && (philo->times_eaten == self->times_must_eat))
		{
			pthread_mutex_lock(&self->mtx_count_philos_already_eaten);
			self->count_times_already_eaten++;
			pthread_mutex_unlock(&self->mtx_count_philos_already_eaten);
			break ;
		}
		eat_sleep_think(philo);
	}
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
	
	// checar se existe número de vezes pra comer argv[5]

	count = 0;
	while (count < self->number_of_philosophers)
	{
		philo = self->philo + count;
		if (pthread_create(philo->thread, NULL, &routine, philo) != 0)
			printf ("Erro ao criar thread\n");
		printf("[create_threads]\tThread |%p| para o filosófo |%d| criada\n", philo->thread, count);
		// faz sentido usar o detach, pois não vou usar o resultado de routine, pra nada, acho
		// pthread_detach(*(philo->thread));
		count++;
	}
	printf("\n");
	count = 0;
	while (count < self->number_of_philosophers)
	{
		philo = self->philo + count;
		if (pthread_join(*(philo->thread), NULL) != 0)
			printf("Erro ao unir thread.\n");
		printf("[join_threads]\tThread |%p| unida\n", philo->thread);
		count++;
	}
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
		printf("Número de argumentos inválidos\n");
		return (FALSE);
	} 
	count = 1;
	while (count < argc)
	{
		if (!ft_isnum(argv[count++])) // checar se parâmetros recebidos contém apenas números
		{
			printf("Paramatros devem conter apenas numeros\n");
			return (FALSE);
		}
	}
	if (argv[1])
	{
		if (ft_atoi(argv[1]) <= 0) // checa se o número de filósofos é maior que zero
		{
			printf("Total de filosofos não pode ser zero\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

// argc[0] -- (char)	program
// argc[1] -- (int)		number_of_philosopher
// argc[2] -- (int)		time_to_die
// argc[3] -- (int)		time_to_eat
// argc[4] -- (int)		time_to_sleep
// argc[5] -- (int)		number_of_times_each_philosopher_must_eat (Opicional)
int main(int argc, char *argv[])
{

	t_config	self;

	if (check_args(argc, argv))
	{
		init_config(&self, --argc, ++argv); //iniciar configurações
		// print_config(&self);
		init_philos(&self); // iniciar filosofos
		create_threads(&self); // criar threads
		pthread_mutex_lock(&self.mtx_gameover);
	}
	else
		return (1);
	return (0);
}
