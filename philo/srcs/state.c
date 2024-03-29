/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:57:35 by roylee            #+#    #+#             */
/*   Updated: 2024/03/23 13:12:54 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_state(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(&philo->app->meal);
	t = get_current_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->app->meal);
	if (t > philo->app->ttd)
	{
		dead_logger(philo, "died", get_current_ms() - philo->philo_start);
		return (DIED);
	}
	return (ALIVE);
}

void	set_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->sim_end);
	philo->app->end = 1;
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
