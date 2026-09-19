/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:02:10 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 17:56:16 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(int c)
{
	return (\
c == '\f' || \
c == '\n' || \
c == '\r' || \
c == '\t' || \
c == '\v' || \
c == ' '\
);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
1- trim whitespace
2- get sign
3- get value
4- return sign*value
*/
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	value;

	while (*nptr && ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	value = 0;
	while (*nptr && ft_isdigit(*nptr))
	{
		value *= 10;
		if (sign == 1)
			value += (*nptr - '0');
		else
			value -= (*nptr - '0');
		nptr++;
	}
	return (value);
}
