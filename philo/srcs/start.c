/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/03/10 17:19:32 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate(t_philo *philos)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (philos[0].app->eat_limit == -1)
		return (NOT_ALL_EATEN);
	while (++i < philos[0].app->philo_nbr)
	{
		pthread_mutex_lock(&philos[i].app->meal);
		if (philos[i].eat_count >= philos[i].app->eat_limit)
			n++;
		pthread_mutex_unlock(&philos[i].app->meal);
	}
	if (philos[0].app->philo_nbr == n)
		return (ALL_ATE);
	return (NOT_ALL_EATEN);
}

// static int isdead(t_philo *philos)
// {
// 	long	t_lastmeal;
// 	int		i;

// 	i = -1;
// 	while (++i < philos[0].app->philo_nbr)
// 	{
// 		pthread_mutex_lock(&philos[i].app->meal);
// 		t_lastmeal = get_time() - philos[i].last_meal;
// 		if (t_lastmeal >= philos[i].app->ttd && philos[i].state != EAT)
// 		{
// 			logger(&philos[i], "died");
// 			pthread_mutex_unlock(&philos[i].app->meal);
// 			pthread_mutex_lock(&philos[i].app->dead);
// 			philos[i].app->end = 1;
// 			philos[i].state = DIED;
// 			pthread_mutex_unlock(&philos[i].app->dead);
// 			return (DIED);
// 		}
// 		pthread_mutex_unlock(&philos[i].app->meal);
// 	}
// 	return (ALIVE);
// }

/*
checks if philo is dead or all philos ate
*/
int		ft_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->meal);
	pthread_mutex_lock(&philo->app->dead);
	if (get_time() - philo->last_meal >= philo->app->ttd && philo->state != EAT)
	{
		printf("test");
		logger(philo, "died");
		philo->app->end = 1;
		philo->state = DIED;
		pthread_mutex_unlock(&philo->app->meal);
		pthread_mutex_unlock(&philo->app->dead);
		return (DIED);
	}
	else if (all_ate(philo) == ALL_ATE)
	{
		philo->app->end = 1;
		pthread_mutex_unlock(&philo->app->meal);
		pthread_mutex_unlock(&philo->app->dead);
		return (ALL_ATE);
	}
	printf("hello2\n");
	pthread_mutex_unlock(&philo->app->meal);
	return (ALIVE);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philos[0].app->philo_nbr)
		{
			printf("hello\n");
			if (ft_state(&philos[i]) == DIED)
				return (arg);
		}
		if (all_ate(philos) == ALL_ATE)
		{
			pthread_mutex_lock(&philos[0].app->dead);
			philos[0].app->end = 1;
			pthread_mutex_unlock(&philos[0].app->dead);
			return (arg);
		}
	}
	return (arg);
}

int		check_dead(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->app->dead);
	end = philo->app->end;
	pthread_mutex_unlock(&philo->app->dead);
	return (end);
}

void	*start_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!check_dead(philo))
	{
		eat(philo);
		psleep(philo);
		think(philo);
	}
	return (arg);
}

void	start(t_prog *app)
{
	pthread_t	watch;
	int			i;

	// printf("%d\n", app->end);
	if (pthread_create(&watch, NULL, &monitor, app->philos) != 0)
		thread_exception(THD_CREAT_FAIL, app);
	i = -1;
	while (++i < app->philo_nbr)
	{
		if (pthread_create(&app->philos[i].tid, NULL, &start_routine, \
				&app->philos[i]) != 0)
			thread_exception(THD_CREAT_FAIL, app);
	}
	if (pthread_join(watch, NULL) != 0)
		thread_exception(THD_JOIN_FAIL, app);
	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_join(app->philos[i].tid, NULL) != 0)
			thread_exception(THD_JOIN_FAIL, app);
	return ;
}
