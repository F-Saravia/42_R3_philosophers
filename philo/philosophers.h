/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:09:51 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 18:46:28 by fasaravi         ###   ########.fr       */
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
# include <stdbool.h>

/* ************************************************************************** */
/* UTILS                                                                      */
/* ************************************************************************** */

# define MSG_FORK "has taken a fork"
# define MSG_EATS "is eating"
# define MSG_SLEAPS "is thinking"
# define MSG_THINKS "died"

void	ft_putstr_fd(int fd, char *s);
void	ft_puts_fd(int fd, char *s);
void	ft_putnbr_fd(int fd, long number);
void	print_philo_isdoing(long timestamp, int phid, char *doing);

bool	ft_isspace(int c);
bool	ft_isdigit(int c);
bool	ft_isnbr(char *s);
int		ft_atoi(const char *nptr);

typedef struct	s_state
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_meals;
}	t_state;

/* ************************************************************************** */
/* PARSING                                                                    */
/* ************************************************************************** */

void	remember_noet(int n_args);
bool	parse_argv(int ac, char **av, t_state *state);

/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

void	test_print_state(t_state *state);

#endif // PHILOSOPHERS_H