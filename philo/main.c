/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:07:20 by roylee            #+#    #+#             */
/*   Updated: 2024/02/25 12:43:02 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog	app;

	if (!(argc == 4 || argc == 5))
		exception("./philo 5 800 200 200 [7]");
	check_input(&app, argc, argv);
	init_app(argc, argv, &app);
	start(&app);
}
