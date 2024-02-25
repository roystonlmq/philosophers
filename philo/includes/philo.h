/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:58:36 by roylee            #+#    #+#             */
/*   Updated: 2024/02/24 09:43:38 by roylee           ###   ########.fr       */
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

# define THD_INIT_FAIL "Thread init failed"
# define THD_JOIN_FAIL "Thread join failed"

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mtx;

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

struct	s_fork
{
	t_mtx		mtx;
	int			id;
};

struct	s_philo
{
	pthread_t	tid;
	t_fork		*left;
	t_fork		*right;
	t_prog		*app;
	long		last_meal;
	int			id;
	int			eat_count;
	int			state;
};

/*
srcs/lib/wildcard.c
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
void	thread_exception(const char *s, t_prog *app);

/*
init.c
*/
void	init_app(int ac, char **av, t_prog *app);

/*
free.c
*/


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
void	start_routine(void *arg);
int		ft_state(t_philo *philo);

/*
parser.c
*/
void	check_input(t_prog *app, int ac, char **av);

#endif