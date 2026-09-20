/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 02:44:50 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/20 04:45:49 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

int	ft_sleep(long duration, t_state *st)
{
	long	end;

	end = get_time() + duration;
	while (!state_get_finished(st) && get_time() < end)
	{
		if (end - get_time() > 1)
			usleep(SLEEP_DELAY);
		else
			usleep(FORK_DELAY);
	}
	return (!state_get_finished(st));
}
