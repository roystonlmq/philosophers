/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:43:35 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 14:33:43 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
check_input:
./philo philo_nbr time_to_die time_to_eat time_to_sleep [optional: eat_limit]
./philo	5	800			200			200				7
			av[1]	av[2]		av[3]		av[4]			av[5]
*/
void	check_inp(t_prog *app, int ac, char **av)
{
	int	i;

	i = -1;
	if (ft_atol(av[1]) <= 0)
		exception("Invalid input\n");
	while (av[++i])
	{
		if (!ft_isnbr(av[i]))
			exception("Invalid input\n");
	}
}