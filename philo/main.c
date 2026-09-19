/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:07:58 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 18:46:09 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_state	state;

	if (ac != 5 && ac != 6)
		return (remember_noet(ac - 1),1);
	memset(&state, 0, sizeof(state));
	if (!parse_argv(ac, av, &state))
		return (1);
test_print_state(&state);
	return (0);
}
