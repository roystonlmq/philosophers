/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:07:20 by roylee            #+#    #+#             */
/*   Updated: 2024/03/10 18:50:57 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog	*app;

	if (!(argc == 5 || argc == 6))
		exception("./philo 5 800 200 200 [7]");
	check_input(argc, argv);
	app = init_app(argc, argv);
	start(app);
	free_app(app);
}
