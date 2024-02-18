/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:58:36 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 13:23:27 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h> // printf
# include <string.h> // memset
# include <stdlib.h> // malloc, free
# include <pthread.h> // pthread_create, pthread_join, pthread_mutex_init, 
//pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy
# include <unistd.h> // usleep, write
# include <sys/time.h> // gettimeofday

typedef struct s_philo	t_philo;

typedef struct	s_prog
{
	t_philo	*philos;
	long	ttd;
	long	tte;
	long	tts;
	int		philo_nbr;
	int		eat_limit;
	int		dead;
}	t_prog;

typedef struct	s_fork
{
	
}

struct	s_philo
{
	int		id;
	t_fork	*left;
	t_fork	*right;
	
}

/*
srcs/lib/*.c
*/
void	*ft_malloc(size_t size);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(const char *s);
int		ft_strlen(const char *s);


/*
error.c
*/
void	exception(const char *s);

/*
init.c
*/

/*
parser.c
*/
void	check_input(int ac, char **av, t_prog *app);

#endif