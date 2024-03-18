/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:50:41 by roylee            #+#    #+#             */
/*   Updated: 2024/03/18 21:57:38 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_philo_ate_cnt(t_philo *philo, int *n)
{
	pthread_mutex_lock(&philo->app->meal);
	if (philo->eat_count >= philo->app->eat_limit)
		(*n)++;
	pthread_mutex_unlock(&philo->app->meal);
}

void	*monitor(void *data)
{
	t_philo	*philos;
	int		i;
	int		n;
	int		e;

	philos = (t_philo *)data;
	e = 1;
	while (e)
	{
		i = -1;
		n = 0;
		while (++i < philos[0].app->philo_nbr && e == 1)
		{
			if (ft_state(&philos[i]) == DIED)
				e = 0;
			if (philos[0].app->eat_limit == -1)
				continue ;
			get_philo_ate_cnt(&philos[i], &n);
			if (philos[0].app->philo_nbr == n)
				e = 0;
			if (e == 0)
				set_end(&philos[0]);
		}
	}
	return (data);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

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
	if (pthread_create(&watch, NULL, (void *)monitor, app->philos) != 0)
		thread_exception(THD_CREAT_FAIL, app);
	if (pthread_join(watch, NULL) != 0)
		thread_exception(THD_JOIN_FAIL, app);
	i = -1;
	while (++i < app->philo_nbr)
		if (pthread_join(app->philos[i].tid, NULL) != 0)
			thread_exception(THD_JOIN_FAIL, app);
	return ;
}
