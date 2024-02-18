/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:58:36 by roylee            #+#    #+#             */
/*   Updated: 2024/02/18 15:25:27 by roylee           ###   ########.fr       */
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
typedef pthread_mutex_t	t_mtx;

typedef enum e_state
{
	THINK,
	EAT,
	SLEEP,
	FORK1,
	FORK2,
	DIED,
}	t_state;

typedef struct	s_prog
{
	pthread_t	*threads;
	t_philo		*philos;
	t_fork		*forks;
	t_mtx		print;
	t_mtx		dead;
	t_mtx		meal;
	long		ttd;
	long		tte;
	long		tts;
	long		start;
	int			philo_nbr;
	int			eat_limit;
	int			end;
}	t_prog;

typedef struct	s_fork
{
	t_mtx		mtx;
	int			id;
}	t_fork;

struct	s_philo
{
	pthread_t	tid;
	t_mtx		philo_mtx;
	t_fork		*left;
	t_fork		*right;
	t_prog		*app;
	long		last_meal;
	int			id;
	int			eat_count;
}	t_philo;

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
time.c
*/
int		ft_usleep(long time);
long	get_time(void);

/*
error.c
*/
void	exception(const char *s);

/*
init.c
*/
void	init_app(t_prog *app, int ac, char **av);

/*
free.c
*/


/*
parser.c
*/
void	check_input(int ac, char **av, t_prog *app);

#endif