/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:37:49 by roylee            #+#    #+#             */
/*   Updated: 2024/03/10 15:18:53 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exception(const char *s)
{
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	thread_exception(const char *s, t_prog *app)
{
	write(2, s, ft_strlen(s));
	free_app(app);
	exit(EXIT_FAILURE);
}
