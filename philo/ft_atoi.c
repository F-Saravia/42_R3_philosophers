/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:02:10 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 18:27:06 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ft_isspace(int c);
bool	ft_isdigit(int c);

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
