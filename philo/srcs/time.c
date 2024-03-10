/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:24:40 by roylee            #+#    #+#             */
/*   Updated: 2024/03/10 16:06:05 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exception("gettimeofday failed\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int		ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		// printf("now: %ld\n, tgt: %ld\n", get_time() - start, time);
		usleep(500);
	}
	return (0);
}
