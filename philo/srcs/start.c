/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/03/23 13:10:33 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_philo_ate_cnt(t_philo *philo, int *n)
{
	pthread_mutex_lock(&philo->app->meal);
	if (philo->eat_count >= philo->app->eat_limit)
		(*n)++;
	pthread_mutex_unlock(&philo->app->meal);
	if (philo->app->philo_nbr == *n)
	{
		set_end(philo);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_philo	*philos;
	int		i;
	int		n;
	int		flag;

	philos = (t_philo *)data;
	flag = 1;
	while (flag)
	{
		i = -1;
		n = 0;
		while (++i < philos[0].app->philo_nbr && flag == 1)
		{
			if (ft_state(&philos[i]) == DIED)
				flag = 0;
			if (philos[0].app->eat_limit == -1)
				continue ;
			if (get_philo_ate_cnt(&philos[i], &n) == 1)
				flag = 0;
		}
	}
	set_end(&philos[0]);
	return (data);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->app->thds_rdy);
		if (philo->app->ready == READY)
		{
			pthread_mutex_unlock(&philo->app->thds_rdy);
			break ;
		}
		pthread_mutex_unlock(&philo->app->thds_rdy);
	}
	if (philo->id % 2 == 0)
		while (check_end(philo) == 0)
			eat_slp_think(philo, 1);
	else
	{
		while (check_end(philo) == 0)
		{
			slp_think(philo);
			eat_slp_think(philo, 0);
		}
	}
	return (arg);
}

static void	app_ready(t_prog *app)
{
	int		i;

	app->start = 0;
	i = -1;
	while (++i < app->philo_nbr)
	{
		if (i == app->philo_nbr - 1)
			app->start = get_current_ms();
	}
	i = -1;
	while (++i < app->philo_nbr)
	{
		app->philos[i].philo_start = app->start;
		app->philos[i].last_meal = app->start;
	}
	pthread_mutex_lock(&app->thds_rdy);
	app->ready = READY;
	pthread_mutex_unlock(&app->thds_rdy);
}

int	start(t_prog *app)
{
	pthread_t	watch;
	int			i;

	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_create(&app->philos[i].tid, NULL, &start_routine, \
				&app->philos[i]) != 0)
			return (thread_exception(THD_CREAT_FAIL, app));
	app_ready(app);
	if (pthread_create(&watch, NULL, &monitor, app->philos) != 0)
		return (thread_exception(THD_CREAT_FAIL, app));
	if (pthread_join(watch, NULL) != 0)
		return (thread_exception(THD_JOIN_FAIL, app));
	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_join(app->philos[i].tid, NULL) != 0)
			return (thread_exception(THD_JOIN_FAIL, app));
	return (SUCCESS);
}
