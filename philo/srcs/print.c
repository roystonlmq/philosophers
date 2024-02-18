/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:57:50 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 15:02:09 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log(t_philo *philo, char *s, int id)
{
	long	t;

	pthread_mutex_lock(&philo->app->print);
	time = get_time() - philo->app->start;
	if (!check_dead(philo))
		printf("%ld %d %s\n", time, id, s);
	pthread_mutex_unlock(&philo->app->print);
}

void	eat(t_philo *philo)
{
	
}