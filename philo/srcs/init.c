/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:43:39 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 14:50:34 by roylee           ###   ########.fr       */
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
		app->forks[i].id = i;
		app->philos[i]->left_fork = &app->forks[(i + 1) % philo_nbr];
		app->philos[i]->right_fork = &app->forks[i];
		if (app->philos[i].id % 2 == 0)
		{
			app->philos[i]->left_fork = &app->forks[i];
			app->philos[i]->right_fork = &app->forks[(i + 1) % philo_nbr];
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
		app->philos[i].last_eat = get_time();
		pthread_mutex_init(&app->philos[i].philo_mtx, NULL);
	}
}

void	init_app(int ac, char **av, t_prog *app)
{
	app->philo_nbr = ft_atol(av[1]);
	app->ttd = ft_atol(av[2]) * 1e3;
	app->tte = ft_atol(av[3]) * 1e3;
	app->tts = ft_atol(av[4]) * 1e3;
	if (ac == 6)
		app->eat_limit = ft_atol(av[5]);
	else
		app->eat_limit = -1;
	app->dead = 0;
	app->philos = ft_malloc(sizeof(t_philo) * app->philo_nbr);
	app->forks = ft_malloc(sizeof(t_mtx) * app->philo_nbr);
	pthread_mutex_init(&app->write_mtx, NULL);
	pthread_mutex_init(&app->app_mtx, NULL);
	init_philos(app);
	init_forks(app);
	start(app);
}