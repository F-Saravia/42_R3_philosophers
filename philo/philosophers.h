/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:09:51 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:46:51 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

typedef struct s_state	t_state;

typedef struct s_fork_gatekeepr
{
	pthread_mutex_t	gate;
	bool			*availables;
	bool			init;
}	t_fork_gatekeeper;

typedef struct s_philosopher
{
	t_state			*state;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	eat_lock;
	int				eat_count;
	bool			eat_hungry;
	long			eat_last;
	long			eat_waiting;
}	t_philo;

typedef struct s_state
{
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_meals;
	long				start_time;
	bool				started;
	bool				finished;
	int					ready_count;
	t_philo				*philos;
	int					philos_ready;
	int					threads_created;
	pthread_mutex_t		*forks;
	int					forks_ready;
	t_fork_gatekeeper	gatekeeper;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		lock_state;
	int					locks_ready;
}	t_state;

bool	state_init(t_state *state);
void	state_clean(t_state *state);
int		state_get_finished(t_state *state);
void	state_set_finished(t_state *state);

/* ************************************************************************** */
/* UTILS                                                                      */
/* ************************************************************************** */

# define MSG_FORK "has taken a fork"
# define MSG_EATS "is eating"
# define MSG_SLEEPS "is sleeping"
# define MSG_THINKS "is thinking"
# define MSG_DEATH "died"

void	ft_putstr_fd(int fd, char *s);
void	ft_puts_fd(int fd, char *s);
void	ft_putnbr_fd(int fd, long number);
void	print_philo_isdoing(t_philo *philo, char *doing);
void	print_philo_isdoing2(long timestamp, int phid, char *doing);

bool	ft_isspace(int c);
bool	ft_isdigit(int c);
bool	ft_ispositivenbr(char *s);
int		ft_atoi(const char *nptr);

long	get_time(void);
int		ft_sleep(long duration, t_state *st);

/* ************************************************************************** */
/* PARSING                                                                    */
/* ************************************************************************** */

void	remember_noet(int n_args);
bool	parse_argv(int ac, char **av, t_state *state);

/* ************************************************************************** */
/* THREADS                                                                    */
/* ************************************************************************** */

# define FORK_DELAY 200
# define SLEEP_DELAY 1000
# define MONITOR_DELAY 500

bool	threads_init(t_state *state);
void	threads_start(t_state *state);
bool	wait_for_start(t_state *state);

/* ************************************************************************** */
/* FORK GATEKEEPR                                                             */
/* ************************************************************************** */

bool	reserve_forks(t_philo *philo);

/* ************************************************************************** */
/* PHILOS DO                                                                  */
/* ************************************************************************** */

// bool	take_forks(t_philo *philo);
// void	release_forks(t_philo *philo);
// void	*one_philosopher(t_philo *philo);
void	*philo_do(void *arg);
bool	check_death(t_philo *philo);
bool	philo_eat(t_philo *philo);

#endif // PHILOSOPHERS_H