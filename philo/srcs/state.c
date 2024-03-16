/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:57:35 by roylee            #+#    #+#             */
/*   Updated: 2024/03/16 12:00:21 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	if (philo->state == DIED)
	{
		pthread_mutex_unlock(&philo->state_lock);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->state_lock);
	return (ALIVE);
}

void	update_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
}

/*
checks if philo is dead or all philos ate
*/
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
		logger(philo, "died");
		update_state(philo, DIED);
		set_end(philo->app);
		return (DIED);
	}
	return (ALIVE);
}

void	set_end(t_prog *app)
{
	pthread_mutex_lock(&app->dead);
	app->end = 1;
	pthread_mutex_unlock(&app->dead);
}

int	check_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->app->dead);
	end = philo->app->end;
	pthread_mutex_unlock(&philo->app->dead);
	return (end);
}
