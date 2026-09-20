/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 04:08:34 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:25:12 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	expired(t_philo *philo, long now)
{
	if (now - philo->eat_last < philo->state->time_die)
		return (false);
	state_set_finished(philo->state);
	print_philo_isdoing2(now - philo->state->start_time, philo->id, MSG_DEATH);
	return (true);
}

bool	check_death(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->state->lock_print);
	pthread_mutex_lock(&philo->eat_lock);
	stopped = state_get_finished(philo->state);
	if (!stopped)
		stopped = expired(philo, get_time());
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&philo->state->lock_print);
	return (stopped);
}

bool	philo_eat(t_philo *philo)
{
	long	now;
	int		started;

	pthread_mutex_lock(&philo->state->lock_print);
	pthread_mutex_lock(&philo->eat_lock);
	started = 0;
	if (!state_get_finished(philo->state))
	{
		now = get_time();
		if (!expired(philo, now))
		{
			philo->eat_last = now;
			print_philo_isdoing2(\
now - philo->state->start_time, philo->id, MSG_EATS);
			started = 1;
		}
	}
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&philo->state->lock_print);
	return (started);
}
