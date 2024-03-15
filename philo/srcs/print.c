/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/03/16 00:48:39 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
}

void	logger(t_philo *philo, char *s)
{
	long	t;
	int		e;

	// printf("e: %d\n", check_end(philo));
	e = check_end(philo);
	pthread_mutex_lock(&philo->app->print);
		// printf("never got here");
	if (e == 0)
	{
		t = get_time() - philo->app->start;
		printf("%ld %d %s\n", t, philo->id, s);
	}
	pthread_mutex_unlock(&philo->app->print);
}

void	think(t_philo *philo)
{
	update_state(philo, THINK);
	logger(philo, "is thinking");
	if (philo->app->philo_nbr % 2 != 0)
		ft_usleep(philo->app->tts);
	if (philo->app->philo_nbr > 105 && philo->id % 2 == 0)
		ft_usleep(philo->app->tts / 2);
	update_state(philo, NONE);
}

void	psleep(t_philo *philo)
{
	long	tts;

	update_state(philo, SLEEP);
	tts = philo->app->tts;
	logger(philo, "is sleeping");
	ft_usleep(tts);
	update_state(philo, NONE);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	logger(philo, "has taken a fork");
	if (philo->app->philo_nbr == 1)
	{
		ft_usleep(philo->app->ttd);
		pthread_mutex_unlock(philo->left);
		return ;
	}
	pthread_mutex_lock(philo->right);
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
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
