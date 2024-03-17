/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:57:35 by roylee            #+#    #+#             */
/*   Updated: 2024/03/17 18:13:47 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo *philo)
{
	int	s;

	pthread_mutex_lock(&philo->state_lock);
	s = philo->state;
	pthread_mutex_unlock(&philo->state_lock);
	if (s == DIED)
		return (DIED);
	return (ALIVE);
}

void	update_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
}


int	ft_state(t_philo *philo)
{
	long	t;
	int		s;

	pthread_mutex_lock(&philo->app->meal);
	t = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->app->meal);
	pthread_mutex_lock(&philo->state_lock);
	s = philo->state;
	pthread_mutex_unlock(&philo->state_lock);
	if (t >= philo->app->ttd && s != EAT)
	{
		pthread_mutex_lock(&philo->app->print);
		set_end(philo);
		logger2(philo, "died");
		pthread_mutex_unlock(&philo->app->print);
		update_state(philo, DIED);
		return (DIED);
	}
	return (ALIVE);
}

void	set_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->sim_end);
	philo->app->end = 1;
	ft_usleep(3);
	pthread_mutex_unlock(&philo->app->sim_end);
}

int	check_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->app->sim_end);
	end = philo->app->end;
	pthread_mutex_unlock(&philo->app->sim_end);
	return (end);
}
