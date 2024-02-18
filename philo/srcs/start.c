/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 15:41:11 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->app->dead);
	if (philo->app->end)
	{
		pthread_mutex_unlock(philo->app->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->app->dead);
	return (0);
}

void	start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!check_dead(philo))
	{
		if (philo->app->end)
			break ;
		eat(philo);
		sleep(philo);
		think(philo);
	}
}

void	start(t_prog *app)
{
	int	i;

	i = -1;
	while (++i < app->philo_nbr)
	{
		pthread_create(&app->philo[i].tid, NULL, &philo, &app->philo[i]);
	}
}