/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:55:47 by harndt            #+#    #+#             */
/*   Updated: 2023/01/23 15:42:44 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

/**
 * @brief Boolean type. TRUE (1)/FALSE (0)
 */
typedef int	t_bool;

// =============================================================================
// FUNCTION
// =============================================================================

t_bool	ft_isnum(char *str);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif