/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_init_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 01:49:28 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:47:17 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	init_forks(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		if (pthread_mutex_init(&((state->forks)[i]), NULL) != 0)
			return (false);
		(state->gatekeeper).availables[i] = true;
		state->forks_ready += 1;
		i++;
	}
	return (true);
}

static bool	init_locks(t_state *state)
{
	if (pthread_mutex_init(&(state->lock_print), NULL) != 0)
		return (false);
	state->locks_ready += 1 ;
	if (pthread_mutex_init(&(state->lock_state), NULL) != 0)
		return (false);
	state->locks_ready += 1;
	if (pthread_mutex_init(&((state->gatekeeper).gate), NULL) != 0)
		return (false);
	(state->gatekeeper).init = true;
	return (true);
}

static bool	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		(state->philos[i]).state = state;
		(state->philos[i]).eat_count = 0 ;
		(state->philos[i]).eat_hungry = false;
		(state->philos[i]).eat_last = 0;
		(state->philos[i]).eat_waiting = 0;
		(state->philos[i]).fork_l = &((state->forks)[i]);
		(state->philos[i]).fork_r = \
&((state->forks)[((i + 1) % state->nb_philo)]);
		if (pthread_mutex_init(&((state->philos)[i]).eat_lock, NULL) != 0)
			return (false);
		state->philos_ready += 1;
		i++;
	}
	return (true);
}

void	state_clean(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_ready)
	{
		pthread_mutex_destroy(&state->philos[i].eat_lock);
		i++;
	}
	i = 0;
	while (i < state->forks_ready)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	if (state->gatekeeper.init)
		pthread_mutex_destroy(&state->gatekeeper.gate);
	if (state->locks_ready >= 2)
		pthread_mutex_destroy(&state->lock_state);
	if (state->locks_ready >= 1)
		pthread_mutex_destroy(&state->lock_print);
	free(state->forks);
	free(state->gatekeeper.availables);
	free(state->philos);
}

bool	state_init(t_state *state)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*availables;

	philos = malloc(state->nb_philo * sizeof(*philos));
	if (!philos)
		return (false);
	forks = malloc(state->nb_philo * sizeof(*forks));
	if (!forks)
		return (free(philos), false);
	availables = malloc(state->nb_philo * sizeof(*availables));
	if (!availables)
		return (free(philos), free(forks), false);
	if (!init_locks(state))
		return (state_clean(state), false);
	if (!init_forks(state))
		return (state_clean(state), false);
	if (!init_philos(state))
		return (state_clean(state), false);
	return (true);
}
