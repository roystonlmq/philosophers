/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:43:39 by roylee            #+#    #+#             */
/*   Updated: 2024/03/22 23:34:50 by roylee           ###   ########.fr       */
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
		app->philos[i].first = &app->forks[i];
		app->philos[i].second = &app->forks[(i + 1) % philo_nbr];
		if (i % 2 == 0)
		{
			app->philos[i].first = &app->forks[(i + 1) % philo_nbr];
			app->philos[i].second = &app->forks[i];
		}
	}
}

static void	init_philos(t_prog *app)
{
	int	i;

	i = -1;
	while (++i < app->philo_nbr)
	{
		app->philos[i].id = i + 1;
		app->philos[i].app = app;
		app->philos[i].eat_count = 0;
		app->philos[i].last_meal = 0;
		app->philos[i].philo_start = 0;
	}
}

/*
init_app
*/
t_prog	*init_app(int ac, char **av)
{
	t_prog	*app;

	app = ft_malloc(sizeof(t_prog));
	app->philo_nbr = ft_atol(av[1]);
	app->ttd = ft_atol(av[2]);
	app->tte = ft_atol(av[3]);
	app->tts = ft_atol(av[4]);
	if (ac == 6)
		app->eat_limit = ft_atol(av[5]);
	else
		app->eat_limit = -1;
	app->philos = ft_malloc(sizeof(t_philo) * app->philo_nbr);
	app->forks = ft_malloc(sizeof(pthread_mutex_t) * app->philo_nbr);
	init_philos(app);
	init_forks(app);
	app->end = 0;
	app->ready = NOT_RDY;
	pthread_mutex_init(&app->meal, NULL);
	pthread_mutex_init(&app->sim_end, NULL);
	pthread_mutex_init(&app->print, NULL);
	pthread_mutex_init(&app->thds_rdy, NULL);
	return (app);
}
