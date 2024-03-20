/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:07:20 by roylee            #+#    #+#             */
/*   Updated: 2024/03/20 18:19:28 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog	*app;

	if (!(argc == 5 || argc == 6))
		return (exception(USAGE));
	if (check_input(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	app = init_app(argc, argv);
	start(app);
	free_app(app);
}
