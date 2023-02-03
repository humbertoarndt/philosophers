/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:55:47 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 13:07:06 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>	// gettimeofday

# define TRUE 1
# define FALSE 0

/**
 * @brief Boolean type. TRUE (1)/FALSE (0)
 */
typedef int	t_bool;

// =============================================================================
// FUNCTION
// =============================================================================

/**
 * @brief Gets the time using the gettimeofday() function.
 * 
 * @return long The time in microseconds.
 */
long	ft_time(void);

/**
 * @brief Find if a Integer is a digit.
 * 
 * @param c Integer containg a position in ASCII.
 * @return Integer greater than or zero if true.
**/
int		ft_isdigit(int c);

/**
 * @brief Suspends the execution for the given microseconds interval.
 * 
 * @param ms The time to wait.
 */
void	ft_usleep(int ms);

/**
 * @brief Checks if the str is a number.
 * 
 * @param str The string to check.
 * @return t_bool If the string only contains numbers TRUE, else FALSE.
 */
t_bool	ft_isnum(char *str);

/**
 * @brief Converts the String to Integer.
 * 
 * @param str String representation of an Integer.
 * @return If converted is done, return the Integer number, in case no 
 * convsersion is possible return zero.
**/
int		ft_atoi(const char *str);

#endif