/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_isdoing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 04:17:33 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:39:24 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo_isdoing(t_philo *philo, char *doing)
{
		t_state	*state;

	state = philo->state;
	pthread_mutex_lock(&state->lock_print);
	if (!state_get_finished(state))
	{
		ft_putnbr_fd(STDOUT_FILENO, get_time() - state->start_time);
		write(STDOUT_FILENO, " ", 1);
		ft_putnbr_fd(STDOUT_FILENO, (long) philo->id);
		write(STDOUT_FILENO, " ", 1);
		ft_puts_fd(STDOUT_FILENO, doing);
	}
	pthread_mutex_unlock(&state->lock_print);
}

void	print_philo_isdoing2(long timestamp, int phid, char *doing)
{
	ft_putnbr_fd(STDOUT_FILENO, timestamp);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(STDOUT_FILENO, (long) phid);
	write(STDOUT_FILENO, " ", 1);
	ft_puts_fd(STDOUT_FILENO, doing);
}
