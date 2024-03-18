/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:37:49 by roylee            #+#    #+#             */
/*   Updated: 2024/03/18 21:17:54 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exception(const char *s)
{
	write(2, s, ft_strlen(s));
	return (EXIT_FAILURE);
}

int	thread_exception(const char *s, t_prog *app)
{
	write(2, s, ft_strlen(s));
	free_app(app);
	return (EXIT_FAILURE);
}
