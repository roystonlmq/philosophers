/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:37:49 by roylee            #+#    #+#             */
/*   Updated: 2024/02/19 22:11:15 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exception(const char *s)
{
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	thread_exception(const char *s, t_prog *app)
{
	int	i;

	i = -1;
	write(2, s, ft_strlen(s));
	pthread_mutex_destroy(&app->print);
	pthread_mutex_destroy(&app->dead);
	pthread_mutex_destroy(&app->meal);
	while (++i < app->philo_nbr)
		if (app->forks[i])
			pthread_mutex_destroy(&app->forks[i]);
	exit(EXIT_FAILURE);
}
