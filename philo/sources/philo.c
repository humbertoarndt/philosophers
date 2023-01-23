/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:22 by harndt            #+#    #+#             */
/*   Updated: 2023/01/23 16:16:07 by harndt           ###   ########.fr       */
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
	self->philo = malloc(sizeof(t_philo) * self->number_of_philosophers);
	if (!self->philo)
		return ;
}

static void	init_philos(t_config *self)
{
	int	count;
	t_philo	*philo;

	count = 0;
	while (count < self->number_of_philosophers)
	{
		printf("criando filósofo |%d|\n", count);
		philo = self->philo + count;
		philo->self = self;
		philo->id = count + 1;
		count++;
	}
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
	// checa se a quantidade adequada de parâmetros foi recebida
	if (argc != 5 && argc != 6)
		valid = FALSE;

	count = 1;
	while (count < argc)
	{
		// checar se parâmetros recebidos contém apenas números
		if (!ft_isnum(argv[count++]))
			valid = FALSE;
	}
	
	// checa se o número de filósofos é maior que zero
	if (ft_atoi(argv[1]) <= 0)
		valid = FALSE;

	if (valid)
	{
		init_config(&self, --argc, ++argv);
		printf("Total of philosophers:\t|%d|\n", self.number_of_philosophers);
		printf("Time to die\t\t|%d|\n", self.time_to_die);
		printf("Time to eat\t\t|%d|\n", self.time_to_eat);
		printf("Time to sleep\t\t|%d|\n", self.time_to_sleep);
		printf("Times to eat\t\t|%d|\n", self.times_must_eat);
		init_philos(&self);
	
	}
	else
		printf("ERROR\n");
	return (0);
}
