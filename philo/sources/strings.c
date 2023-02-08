/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:43:07 by harndt            #+#    #+#             */
/*   Updated: 2023/02/08 12:57:22 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a String contains only digits between 0 ~ 9.
 * 
 * @param str The String to be checked.
 * @return t_bool TRUE if the String contains only digits, else FALSE;
 */
static t_bool	ft_isdigt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Converts a String into an integer.
 * 
 * @param str The String to convert.
 * @return int The converted String.
 */
int	ft_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/**
 * @brief Checkes if the args received by command line are correct.
 * 
 * @param argc Total number of args received by command line.
 * @param argv Args received by command line.
 * @return t_bool If arguments are valid TRUE, else FALSE.
 */
t_bool	is_valid_input(int argc, char *argv[])
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!ft_isdigt(argv[i]))
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], FALSE));
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (msg(STR_MAX_PHILOS, STR_MAX_PHILOS, FALSE));
		if (i != 1 && nb == -1)
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], FALSE));
		i++;
	}
	return (TRUE);
}
