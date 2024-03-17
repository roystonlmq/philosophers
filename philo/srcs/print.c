/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/03/17 18:08:15 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logger(t_philo *philo, char *s)
{
	long	t;

	pthread_mutex_lock(&philo->app->print);
	t = get_time() - philo->app->start;
	if (check_end(philo) == 0 && t >= 0 && t <= LONG_MAX)
		printf("%ld %d %s\n", t, philo->id, s);
	pthread_mutex_unlock(&philo->app->print);
}

void	logger2(t_philo *philo, char *s)
{
	long	t;

	t = get_time() - philo->app->start;
	printf("%ld %d %s\n", t, philo->id, s);
}

/*
formula for hunger:
hunger = (time to die - time since last meal - time taken to eat)
time to think is hunger / 2 for buffer
*/
void	think(t_philo *philo)
{
	long	ttt;

	pthread_mutex_lock(&philo->app->meal);
	ttt = (philo->app->ttd - (get_time() - philo->last_meal)
			- philo->app->tte) / 2;
	pthread_mutex_unlock(&philo->app->meal);
	if (ttt < 0)
		ttt = 0;
	if (ttt == 0)
		ttt = 1;
	if (ttt > 600)
		ttt = 200;
	update_state(philo, THINK);
	printf("id: %d e: %d\n", philo->id, check_end(philo));
	logger(philo, "is thinking");
	ft_usleep(ttt);
	update_state(philo, NONE);
}

void	psleep(t_philo *philo)
{
	long	tts;

	update_state(philo, SLEEP);
	tts = philo->app->tts;
	printf("id: %d e: %d\n", philo->id, check_end(philo));
	logger(philo, "is sleeping");
	ft_usleep(tts);
	update_state(philo, NONE);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first);
	logger(philo, "has taken a fork");
	if (philo->app->philo_nbr == 1)
	{
		ft_usleep(philo->app->ttd);
		pthread_mutex_unlock(philo->second);
		return ;
	}
	pthread_mutex_lock(philo->second);
	logger(philo, "has taken a fork");
	update_state(philo, EAT);
	logger(philo, "is eating");
	pthread_mutex_lock(&philo->app->meal);
	philo->eat_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->app->meal);
	ft_usleep(philo->app->tte);
	if (philo->app->ttd < philo->app->tte)
		ft_usleep(philo->app->ttd);
	update_state(philo, NONE);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second);
}
