/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:22 by harndt            #+#    #+#             */
/*   Updated: 2023/01/25 18:56:44 by harndt           ###   ########.fr       */
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

static void	*routine()
{
	printf("[create_threads]\tThread |%ld| criada\n", pthread_self());
	sleep(5);
}

/**
 * @brief Create a threads object
 * 
 * @param self 
 */
static void	create_threads(t_config *self)
{
	int	count;
	t_philo	*philo;
	
	count = 0;
	printf("Criar |%d| threads\n", self->number_of_philosophers);
	while (count < self->number_of_philosophers)
	{
		printf("|%d|\n", count);
		philo = self->philo + count;
		if (pthread_create(philo->thread, NULL, &routine, NULL) != 0)
			printf ("Erro ao criar thread\n");
		// printf("[create_threads]\tThread |%p| para o filosófo |%d| criada\n", philo->thread, count);
		pthread_detach(*(philo->thread));
		count++;
	}
	printf("\n");
}

static void	print_config(t_config *self)
{
	printf("Total of philosophers:\t|%d|\n", self->number_of_philosophers);
	printf("Time to die\t\t|%d|\n", self->time_to_die);
	printf("Time to eat\t\t|%d|\n", self->time_to_eat);
	printf("Time to sleep\t\t|%d|\n", self->time_to_sleep);
	printf("Times to eat\t\t|%d|\n", self->times_must_eat);
}

// argc[0] -- (char)	program
// argc[1] -- (int)		number_of_philosopher
// argc[2] -- (int)		time_to_die
// argc[3] -- (int)		time_to_eat
// argc[4] -- (int)		time_to_sleep
// argc[5] -- (int)		number_of_times_each_philosopher_must_eat (Opicional)
int main(int argc, char *argv[])
{
	int	count;
	t_bool	valid;
	t_config	self;
	
	valid = TRUE;
	if (argc != 5 && argc != 6) // checa se a quantidade adequada de parâmetros foi recebida
		valid = FALSE;
	count = 1;
	while (count < argc)
	{
		if (!ft_isnum(argv[count++])) // checar se parâmetros recebidos contém apenas números
			valid = FALSE;
	}
	if (argv[1])
	{
		if (ft_atoi(argv[1]) <= 0) // checa se o número de filósofos é maior que zero
			valid = FALSE;
	}
	if (valid)
	{
		init_config(&self, --argc, ++argv); //iniciar configurações
		// print_config(&self);
		init_philos(&self); // iniciar filosofos
		create_threads(&self); // criar threads
	}
	else
		printf("ERROR\n");
	return (0);
}
