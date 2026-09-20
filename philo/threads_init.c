/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 02:31:21 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 03:39:23 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	all_ate_enough(t_state *state)
{
	int	i;
	int	complete;

	if (state->nb_meals == -1)
		return (0);
	i = 0;
	while (i < state->nb_philo)
	{
		pthread_mutex_lock(&state->philos[i].eat_lock);
		complete = (state->philos[i].eat_count >= state->nb_meals);
		pthread_mutex_unlock(&state->philos[i].eat_lock);
		if (!complete)
			return (false);
		i++;
	}
	return (true);
}

static void	monitor(t_state *state)
{
	int	i;

	while (!state_get_finished(state))
	{
		i = 0;
		while (i < state->nb_philo)
		{
			if (check_death(&state->philos[i++]))
				return ;
		}
		if (all_ate_enough(state))
		{
			pthread_mutex_lock(&state->lock_print);
			state_set_finished(state);
			pthread_mutex_unlock(&state->lock_print);
			return ;
		}
		usleep(MONITOR_DELAY);
	}
}

static void	join_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->threads_created)
	{
		pthread_join(state->philos[i].thread, NULL);
		i++;
	}
}

bool	threads_init(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		if (pthread_create(&state->philos[i].thread, NULL,
				philo_do, &state->philos[i]) != 0)
		{
			state_set_finished(state);
			join_threads(state);
			return (false);
		}
		state->threads_created++;
		i++;
	}
	threads_start(state);
	monitor(state);
	join_threads(state);
	return (true);
}
