/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 18:44:46 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 19:49:10 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	remember_noet(int n_args)
{
	ft_puts_fd(STDERR_FILENO, "Expected number of arguments: 4[+1]");
	ft_putstr_fd(STDERR_FILENO, "Received ");
	ft_putnbr_fd(STDERR_FILENO, (long) n_args);
	ft_puts_fd(STDERR_FILENO, " arguments");
	ft_puts_fd(STDERR_FILENO,\
"./philo nb_philos time_die time_eat time_sleep [nb_meals]\n");
}

bool	parse_argv(int ac, char **av, t_state *state)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_ispositivenbr(av[i]))
		{
			ft_puts_fd(STDERR_FILENO, "Expect args to be positive numbers");
			return (false);
		}
		i++;
	}
	state->nb_philo = ft_atoi(av[1]);
	state->time_die = ft_atoi(av[2]);
	state->time_eat = ft_atoi(av[3]);
	state->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->nb_meals = ft_atoi(av[5]);
	else
		state->nb_meals = -1;
	return (true);
}
