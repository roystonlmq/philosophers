/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/03/20 18:16:18 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_philo_ate_cnt(t_philo *philo, int *n)
{
	pthread_mutex_lock(&philo->app->meal);
	if (philo->eat_count >= philo->app->eat_limit)
		(*n)++;
	pthread_mutex_unlock(&philo->app->meal);
	if (philo->app->philo_nbr == *n)
		return (set_end(philo));
}

void	*monitor(void *data)
{
	t_philo	*philos;
	int		i;
	int		n;

	philos = (t_philo *)data;
	while (philos[0].app->end == 0)
	{
		i = -1;
		n = 0;
		while (++i < philos[0].app->philo_nbr)
		{
			if (philos[0].app->end == 1 || ft_state(&philos[i]) == DIED)
				break ;
			if (philos[0].app->eat_limit == -1)
				continue ;
			get_philo_ate_cnt(&philos[i], &n);
		}
	}
	return (data);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->app->ready == NOT_RDY)
		continue ;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (check_end(philo) == 0)
		eat_slp_think(philo);
	return (arg);
}

void	start(t_prog *app)
{
	pthread_t	watch;
	int			i;

	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_create(&app->philos[i].tid, NULL, &start_routine, \
				&app->philos[i]) != 0)
			thread_exception(THD_CREAT_FAIL, app);
	i = -1;
	app->start = get_current_ms();
	while (++i < app->philo_nbr)
	{
		app->philos[i].philo_start = app->start;
		app->philos[i].last_meal = app->start;
	}
	app->ready = READY;
	while (app->ready == NOT_RDY)
		continue ;
	if (pthread_create(&watch, NULL, &monitor, app->philos) != 0)
		thread_exception(THD_CREAT_FAIL, app);
	if (pthread_join(watch, NULL) != 0)
		thread_exception(THD_JOIN_FAIL, app);
	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_join(app->philos[i].tid, NULL) != 0)
			thread_exception(THD_JOIN_FAIL, app);
	return ;
}
