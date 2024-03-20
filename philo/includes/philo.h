/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:58:36 by roylee            #+#    #+#             */
/*   Updated: 2024/03/20 19:29:07 by roylee           ###   ########.fr       */
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
# include <limits.h> // INT_MAX
# include <sys/types.h>

# define THD_CREAT_FAIL "Thread create failed"
# define THD_JOIN_FAIL "Thread join failed"
# define USAGE "Usage: ./philo philo_nbr ttd tte tts [eat_limit]\n"
# define SUCCESS 1

typedef struct s_philo	t_philo;

typedef enum e_state
{
	THINK,
	EAT,
	SLEEP,
	DIED,
	ALL_ATE,
	NOT_ALL_EATEN,
	ALIVE,
	NONE,
	READY,
	NOT_RDY
}	t_state;

typedef struct s_prog
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	sim_end;
	pthread_mutex_t	meal;
	pthread_mutex_t	time;
	pthread_mutex_t	thds_rdy;
	t_philo			*philos;
	long			ttd;
	long			tte;
	long			tts;
	long			start;
	int				philo_nbr;
	int				eat_limit;
	int				ready;
	int				end;
}	t_prog;

struct	s_philo
{
	pthread_mutex_t		*first;
	pthread_mutex_t		*second;
	pthread_t			tid;
	t_prog				*app;
	long				last_meal;
	long				philo_start;
	int					id;
	int					eat_count;
	int					eat_limit;
};

/*
srcs/lib/wildcard.c
*/
size_t	ft_strlen(const char *s);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(const char *s);
void	*ft_malloc(size_t size);

/*
time.c
*/
long	get_current_ms(void);
void	ft_sleep(long time);

/*
error.c
*/
int		exception(const char *s);
int		thread_exception(const char *s, t_prog *app);

/*
init.c
*/
t_prog	*init_app(int ac, char **av);

/*
free.c
*/
void	free_app(t_prog *app);

/*
state.c
*/
int		ft_state(t_philo *philo);
int		check_end(t_philo *app);
void	set_end(t_philo *philo);

/*
print.c
*/
void	logger(t_philo *philo, char *s);
void	dead_logger(t_philo *philo, char *s);
void	eat_slp_think(t_philo *philo);

/*
start.c
*/
int		start(t_prog *app);
void	*start_routine(void *arg);
void	*monitor(void *data);

/*
parser.c
*/
int		check_input(int ac, char **av);

#endif