/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:24:40 by roylee            #+#    #+#             */
/*   Updated: 2024/03/20 18:44:38 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "Error: gettimeofday\n", 19);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long time)
{
	long	start;

	start = get_current_ms();
	while ((get_current_ms() - start) < time)
		usleep(100);
}
