/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:07:58 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 17:58:17 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	remember_noet(int n_args)
{
	ft_puts_fd(STDERR_FILENO, "Expected number of arguments: 4[+1]");
	ft_putstr_fd(STDERR_FILENO, "Received ");
	ft_putnbr_fd(STDERR_FILENO, (long) n_args);
	ft_puts_fd(STDERR_FILENO, " arguments");
	ft_puts_fd(STDERR_FILENO,\
"./philo nb_philos time_die time_eat time_sleep [nb_meals]\n");
}

static void	parse_argv(int ac, char **av, t_state *state)
{
	state->nb_philo = ft_atoi(av[1]);
	state->time_die = ft_atoi(av[2]);
	state->time_eat = ft_atoi(av[3]);
	state->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->nb_meals = ft_atoi(av[5]);
	else
		state->nb_meals = -1;
}

int	main(int ac, char **av)
{
	t_state	state;

	if (ac != 5 && ac != 6)
		return (remember_noet(ac - 1),1);
	memset(&state, 0, sizeof(state));
	parse_argv(ac, av, &state);
	test_print_state(&state);
	return (0);
}
