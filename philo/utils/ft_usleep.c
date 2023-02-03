/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:26:59 by harndt            #+#    #+#             */
/*   Updated: 2023/02/02 11:27:55 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	while ((ft_time() - time) < ms)
		usleep(ms);
}