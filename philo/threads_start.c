/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 03:20:57 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 03:29:23 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	wait_for_start(t_state *state)
{
	int	started;
	int	finished;

	pthread_mutex_lock(&state->lock_state);
	state->ready_count++;
	while (1)
	{
		started = state->started;
		finished = state->finished;
		pthread_mutex_unlock(&state->lock_state);
		if (started || finished)
			return (!finished);
		usleep(FORK_DELAY);
		pthread_mutex_lock(&state->lock_state);
	}
}

static int	all_ready(t_state *state)
{
	int	ready;

	pthread_mutex_lock(&state->lock_state);
	ready = (state->ready_count == state->nb_philo);
	pthread_mutex_unlock(&state->lock_state);
	return (ready);
}

static void	initialize_meals(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		pthread_mutex_lock(&state->philos[i].eat_lock);
		state->philos[i].eat_last = state->start_time;
		pthread_mutex_unlock(&state->philos[i].eat_lock);
		i++;
	}
}

/* Seed first requests together, independently of thread creation order. */
static void	initialize_requests(t_state *state)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&state->gatekeeper.gate);
	while (i < state->nb_philo)
	{
		state->philos[i].eat_hungry = true;
		state->philos[i].eat_waiting = state->start_time;
		i++;
	}
	pthread_mutex_unlock(&state->gatekeeper.gate);
}

void	threads_start(t_state *state)
{
	while (!all_ready(state))
		usleep(FORK_DELAY);
	pthread_mutex_lock(&state->lock_state);
	state->start_time = get_time();
	pthread_mutex_unlock(&state->lock_state);
	initialize_meals(state);
	initialize_requests(state);
	pthread_mutex_lock(&state->lock_state);
	state->started = 1;
	pthread_mutex_unlock(&state->lock_state);
}
