/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 03:35:03 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:43:31 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (reserve_forks(philo))
		return (true);
	first = philo->fork_l;
	second = philo->fork_r;
	if (first > second)
	{
		first = philo->fork_r;
		second = philo->fork_l;
	}
	pthread_mutex_lock(first);
	print_philo_isdoing(philo, MSG_FORK);
	pthread_mutex_lock(second);
	print_philo_isdoing(philo, MSG_FORK);
	return (false);
}

static void	eat(t_philo *philo)
{
	if (!philo_eat(philo))
		return ;
	if (!ft_sleep(philo->state->time_eat, philo->state))
		return ;
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->eat_count < INT_MAX)
		philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_lock);
}

static void	release_forks(t_philo *philo)
{
	t_state	*state;

	state = philo->state;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_lock(&state->gatekeeper.gate);
	state->gatekeeper.availables[philo->id - 1] = 1;
	state->gatekeeper.availables[philo->id % state->nb_philo] = 1;
	pthread_mutex_unlock(&state->gatekeeper.gate);
}

static void	*one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->gatekeeper.gate);
	philo->state->gatekeeper.availables[0] = 0;
	pthread_mutex_unlock(&philo->state->gatekeeper.gate);
	pthread_mutex_lock(philo->fork_l);
	print_philo_isdoing(philo, MSG_FORK);
	while (!state_get_finished(philo->state))
		usleep(FORK_DELAY);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(&philo->state->gatekeeper.gate);
	philo->state->gatekeeper.availables[0] = 1;
	pthread_mutex_unlock(&philo->state->gatekeeper.gate);
	return (NULL);
}

void	*philo_do(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!wait_for_start(philo->state))
		return (NULL);
	if (philo->state->nb_philo == 1)
		return (one_philosopher(philo));
	while (!state_get_finished(philo->state))
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		release_forks(philo);
		if (state_get_finished(philo->state))
			break ;
		print_philo_isdoing(philo, MSG_SLEEPS);
		ft_sleep(philo->state->time_sleep, philo->state);
		print_philo_isdoing(philo, MSG_THINKS);
	}
	return (NULL);
}
