/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 02:40:41 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:45:21 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	state_get_finished(t_state *state)
{
	int	finished;

	pthread_mutex_lock(&state->lock_state);
	finished = state->finished;
	pthread_mutex_unlock(&state->lock_state);
	return (finished);
}

void	state_set_finished(t_state *state)
{
	pthread_mutex_lock(&state->lock_state);
	state->finished = true;
	pthread_mutex_unlock(&state->lock_state);
}
