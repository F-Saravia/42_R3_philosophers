/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:07:58 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:47:47 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_state	state;
	bool	succces;

	if (ac != 5 && ac != 6)
		return (remember_noet(ac - 1), 1);
	memset(&state, 0, sizeof(state));
	if (!parse_argv(ac, av, &state))
		return (1);
	if (state_init(&state))
	{
		ft_puts_fd(STDERR_FILENO, "Error: initialization failed");
		return (1);
	}
	succces = threads_init(&state);
	state_clean(&state);
	if (!succces)
		ft_puts_fd(STDERR_FILENO, "Error: thread creation failed");
	return (0);
}
