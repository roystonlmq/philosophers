/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:43:39 by roylee            #+#    #+#             */
/*   Updated: 2024/03/17 12:59:48 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_prog *app)
{
	int	philo_nbr;
	int	i;

	i = -1;
	philo_nbr = app->philo_nbr;
	while (++i < philo_nbr)
	{
		pthread_mutex_init(&app->forks[i], NULL);
		app->philos[i].left = &app->forks[i];
		if (i == 0)
			app->philos[i].right = &app->forks[philo_nbr - 1];
		else
			app->philos[i].right = &app->forks[i - 1];
	}
}

// can try to init mutexes on app level instead of philo level
static void	init_philos(t_prog *app)
{
	int	i;

	i = -1;
	while (++i < app->philo_nbr)
	{
		app->philos[i].id = i + 1;
		app->philos[i].app = app;
		app->philos[i].eat_count = 0;
		app->philos[i].last_meal = get_time();
		app->philos[i].state = NONE;
		pthread_mutex_init(&app->philos[i].state_lock, NULL);
	}
}

/*
init_app
*/
t_prog	*init_app(int ac, char **av)
{
	t_prog	*app;

	app = ft_malloc(sizeof(t_prog));
	app->threads = NULL;
	app->philo_nbr = ft_atol(av[1]);
	if (ac == 6)
		app->eat_limit = ft_atol(av[5]);
	else
		app->eat_limit = -1;
	app->philos = ft_malloc(sizeof(t_philo) * app->philo_nbr);
	init_philos(app);
	app->forks = ft_malloc(sizeof(pthread_mutex_t) * app->philo_nbr);
	init_forks(app);
	app->ttd = ft_atol(av[2]);
	app->tte = ft_atol(av[3]);
	app->tts = ft_atol(av[4]);
	app->start = get_time();
	app->end = 0;
	pthread_mutex_init(&app->meal, NULL);
	pthread_mutex_init(&app->dead, NULL);
	pthread_mutex_init(&app->print, NULL);
	return (app);
}
