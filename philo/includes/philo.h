/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:58:36 by roylee            #+#    #+#             */
/*   Updated: 2024/03/17 15:16:57 by roylee           ###   ########.fr       */
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

# define THD_CREAT_FAIL "Thread create failed"
# define THD_JOIN_FAIL "Thread join failed"
# define USAGE "Usage: ./philo philo_nbr ttd tte tts [eat_limit]\n"

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
}	t_state;

typedef struct s_prog
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
	t_philo			*philos;
	long			ttd;
	long			tte;
	long			tts;
	long			start;
	int				philo_nbr;
	int				eat_limit;
	int				end;
}	t_prog;

struct	s_philo
{
	pthread_mutex_t		*first;
	pthread_mutex_t		*sec;
	pthread_mutex_t		state_lock;
	pthread_t			tid;
	t_prog				*app;
	long				last_meal;
	int					id;
	int					eat_count;
	int					eat_limit;
	int					state;
	int					philo_nbr;
};

/*
srcs/lib/wildcard.c
*/
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_malloc(size_t size);

/*
time.c
*/
long	get_time(void);
int		ft_usleep(long time);

/*
error.c
*/
void	exception(const char *s);
void	thread_exception(const char *s, t_prog *app);

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
int		check_state(t_philo *philo);
int		check_end(t_philo *app);
void	update_state(t_philo *philo, int state);
void	set_end(t_prog *app);

/*
print.c
*/
void	logger(t_philo *philo, char *s);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	psleep(t_philo *philo);

/*
start.c
*/
void	start(t_prog *app);
void	*start_routine(void *arg);
void	*monitor(void *arg);

/*
parser.c
*/
void	check_input(int ac, char **av);

#endif