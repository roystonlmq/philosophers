/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/03/24 16:01:48 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logger(t_philo *philo, char *s, char *s2)
{
	long	t;

	pthread_mutex_lock(&philo->app->print);
	if (check_end(philo) == 1)
	{
		pthread_mutex_unlock(&philo->app->print);
		return ;
	}
	t = get_current_ms() - philo->philo_start;
	if (!s2)
		printf("%ld %d %s\n", t, philo->id, s);
	if (s && s2)
		printf("%ld %d %s\n%ld %d %s\n", t, philo->id, s, t, philo->id, s2);
	pthread_mutex_unlock(&philo->app->print);
}

void	dead_logger(t_philo *philo, char *s, long t)
{
	pthread_mutex_lock(&philo->app->print);
	printf("%ld %d %s\n", t, philo->id, s);
	set_end(philo);
	pthread_mutex_unlock(&philo->app->print);
}

static void	one_philo(t_philo *philo)
{
	ft_sleep(philo->app->ttd);
	pthread_mutex_unlock(philo->first);
	set_end(philo);
}

void	slp_think(t_philo *philo)
{
	long	ttt;

	logger(philo, "is sleeping", 0);
	ft_sleep(philo->app->tts);
	logger(philo, "is thinking", 0);
	ttt = philo->app->ttd - (get_current_ms() - 
			philo->app->tte - philo->last_meal);
	if (ttt > 2)
		ft_sleep(2);
}

void	eat_slp_think(t_philo *philo, int to_slp)
{
	pthread_mutex_lock(philo->first);
	logger(philo, "has taken a fork", 0);
	if (philo->app->philo_nbr == 1)
		return (one_philo(philo));
	pthread_mutex_lock(philo->second);
	logger(philo, "has taken a fork", "is eating");
	pthread_mutex_lock(&philo->app->meal);
	philo->last_meal = get_current_ms();
	pthread_mutex_unlock(&philo->app->meal);
	ft_sleep(philo->app->tte);
	pthread_mutex_lock(&philo->app->meal);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->app->meal);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second);
	if (to_slp)
		slp_think(philo);
}
