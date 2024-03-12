/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:39:03 by roylee            #+#    #+#             */
/*   Updated: 2024/03/12 23:49:12 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_app(t_prog *app)
{
	int	i;

	pthread_mutex_destroy(&app->meal);
	pthread_mutex_destroy(&app->dead);
	pthread_mutex_destroy(&app->print);
	i = -1;
	while (++i < app->philo_nbr)
		pthread_mutex_destroy(&app->forks[i]);
	free(app->philos);
	free(app->forks);
	free(app);
}
