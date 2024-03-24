/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:09:13 by roylee            #+#    #+#             */
/*   Updated: 2024/03/24 14:13:47 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_odd_start(t_prog *app)
{
	if (app->philo_nbr % 2 != 0)
		return ;
	while (1)
	{
		pthread_mutex_lock(&app->thds_rdy);
		if (app->ready == READY)
		{
			pthread_mutex_unlock(&app->thds_rdy);
			break ;
		}
		pthread_mutex_unlock(&app->thds_rdy);
	}
}

void	app_ready(t_prog *app)
{
	int		i;

	app->start = 0;
	i = -1;
	while (++i < app->philo_nbr)
	{
		if (i == app->philo_nbr - 1)
			app->start = get_current_ms();
	}
	i = -1;
	while (++i < app->philo_nbr)
	{
		app->philos[i].philo_start = app->start;
		app->philos[i].last_meal = app->start;
	}
	pthread_mutex_lock(&app->thds_rdy);
	app->ready = READY;
	pthread_mutex_unlock(&app->thds_rdy);
}
