/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:41:23 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 16:20:54 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_args(int argc, char **argv)
{
	int	count;

	if (argc != 5 && argc != 6)
	{
		printf("%s<USAGE>%s Number of arguments invalid.\n", BYELLOW, EOC);
		return (FALSE);
	}
	count = 1;
	while (count < argc)
	{
		if (!ft_isnum(argv[count++]))
		{
			printf("%s<USAGE>%s All argumetns must be int.\n", BYELLOW, EOC);
			return (FALSE);
		}
	}
	if (argv[1])
	{
		if (ft_atoi(argv[1]) <= 0)
		{
			printf("%s<USAGE>%s Number of philosophers must be greater than 0.\
\n", BYELLOW, EOC);
			return (FALSE);
		}
	}
	return (TRUE);
}
