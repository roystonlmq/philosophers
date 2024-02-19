/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/02/19 22:00:47 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logger(t_philo *philo, char *s)
{
	long	t;

	pthread_mutex_lock(&philo->app->print);
	time = get_time() - philo->app->start;
	if (!check_dead(philo))
		printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->app->print);
}

void	think(t_philo *philo)
{
	philo->state = THINKING;
	logger(philo, "is thinking");
}

void	psleep(t_philo *philo)
{
	long	tts;

	tts = philo->app->tts;
	philo->state = SLEEPING;
	logger(philo, "is sleeping");
	ft_usleep(tts);
}


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	logger(philo, "has taken a fork");
	if (philo->app->philo_num == 1)
	{
		ft_usleep(philo->app->ttd);
		pthread_mutex_unlock(&philo->left);
		return ;
	}
	pthread_mutex_lock(&philo->right);
	logger(philo, "has taken a fork");
	pthread_mutex_lock(&philo->app->meal);
	philo->last_eat = get_time();
	philo->state = EATING;
	logger(philo, "is eating");
	philo->eat_count++;
	philo->state = NONE;
	ft_usleep(philo->app->tte);
	pthread_mutex_unlock(&philo->app->meal);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
}
