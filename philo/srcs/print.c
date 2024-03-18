/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/03/18 22:15:01 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logger(t_philo *philo, char *s)
{
	long	t;

	t = get_time() - philo->app->start;
	pthread_mutex_lock(&philo->app->print);
	if (check_end(philo) == 0 && t >= 0 && t <= LONG_MAX)
		printf("%ld %d %s\n", t, philo->id, s);
	pthread_mutex_unlock(&philo->app->print);
}

void	dead_logger(t_philo *philo, char *s)
{
	long	t;

	pthread_mutex_lock(&philo->app->print);
	set_end(philo);
	t = get_time() - philo->app->start;
	printf("%ld %d %s\n", t, philo->id, s);
	pthread_mutex_unlock(&philo->app->print);
}

static void	slp_think(t_philo *philo)
{
	long	tts;


	tts = philo->app->tts;
	logger(philo, "is sleeping");
	ft_sleep(tts);
	logger(philo, "is thinking");
}

void	eat_slp_think(t_philo *philo)
{
	pthread_mutex_lock(philo->first);
	logger(philo, "has taken a fork");
	if (philo->app->philo_nbr == 1)
	{
		ft_sleep(philo->app->ttd);
		pthread_mutex_unlock(philo->second);
		return ;
	}
	pthread_mutex_lock(philo->second);
	logger(philo, "has taken a fork");
	logger(philo, "is eating");
	pthread_mutex_lock(&philo->app->meal);
	philo->eat_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->app->meal);
	ft_sleep(philo->app->tte);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second);
	slp_think(philo);
}
