/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_gatekeeper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 02:26:09 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:47:29 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	forks_are_free(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->state->nb_philo;
	return (philo->state->gatekeeper.availables[left]
		&& philo->state->gatekeeper.availables[right]);
}

static int	has_priority(t_philo *other, t_philo *philo)
{
	if (!other->eat_hungry)
		return (0);
	if (other->eat_waiting != philo->eat_waiting)
		return (other->eat_waiting < philo->eat_waiting);
	if (other->id % 2 != philo->id % 2)
		return (other->id % 2 > philo->id % 2);
	return (other->id < philo->id);
}

static int	can_take_forks(t_philo *philo)
{
	t_state	*state;
	int		left;
	int		right;

	if (!forks_are_free(philo))
		return (0);
	state = philo->state;
	left = philo->id - 2;
	if (left < 0)
		left = state->nb_philo - 1;
	right = philo->id % state->nb_philo;
	return (!has_priority(&state->philos[left], philo)
		&& !has_priority(&state->philos[right], philo));
}

bool	reserve_forks(t_philo *philo)
{
	t_state	*state;
	bool	stopped;

	state = philo->state;
	pthread_mutex_lock(&state->gatekeeper.gate);
	if (!philo->eat_hungry)
		philo->eat_waiting = get_time();
	philo->eat_hungry = 1;
	while (!state_get_finished(state) && !can_take_forks(philo))
	{
		pthread_mutex_unlock(&state->gatekeeper.gate);
		usleep(FORK_DELAY);
		pthread_mutex_lock(&state->gatekeeper.gate);
	}
	stopped = state_get_finished(state);
	if (!stopped)
	{
		state->gatekeeper.availables[philo->id - 1] = 0;
		state->gatekeeper.availables[philo->id % state->nb_philo] = 0;
	}
	philo->eat_hungry = 0;
	pthread_mutex_unlock(&state->gatekeeper.gate);
	return (stopped);
}
