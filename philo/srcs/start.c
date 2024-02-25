/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/02/25 12:47:45 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->app->philo_nbr)
	{
		if (philo->app->philos[i].eat_count < philo->app->eat_limit)
			return (ALIVE);
	}
	philo->app->end = 1;
	return (ALL_ATE);
}

/*
checks if philo is dead or all philos ate
*/
int		ft_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->dead);
	pthread_mutex_lock(&philo->app->meal);
	if (get_time() - philo->last_meal >= philo->app->ttd && philo->state != EAT)
	{
		logger(philo, "died");
		philo->app->end = 1;
		pthread_mutex_unlock(&philo->app->meal);
		pthread_mutex_unlock(&philo->app->dead);
		return (DIED);
	}
	if (all_ate(philo) == ALL_ATE)
	{
		philo->app->end = 1;
		pthread_mutex_unlock(&philo->app->meal);
		pthread_mutex_unlock(&philo->app->dead);
		return (ALL_ATE);
	}
	pthread_mutex_unlock(&philo->app->meal);
	pthread_mutex_unlock(&philo->app->dead);
	return (ALIVE);
}

void	*start_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (ft_state(philo) != DIED || ft_state(philo) != ALL_ATE)
	{
		eat(philo);
		psleep(philo);
		think(philo);
	}
	return (arg);
}

void	start(t_prog *app)
{
	int	i;

	i = -1;
	while (++i < app->philo_nbr)
	{
		if (pthread_create(&app->philos[i].tid, NULL, &start_routine, 
			&app->philos[i]) != 0)
			thread_exception(THD_CREAT_FAIL, app);
	}
	i = -1;
	while (++i < app->philo_nbr)
		pthread_join(app->philos[i].tid, NULL);
	return ;
}
