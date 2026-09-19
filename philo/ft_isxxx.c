/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxxx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 18:10:55 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 19:47:53 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ft_isspace(int c)
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

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
//
// bool	ft_isnbr(char *s)
// {
// 	while (*s && ft_isspace(*s))
// 		s++;
// 	if (*s == '-' || *s == '+')
// 		s++;
// 	while (*s)
// 	{
// 		if (!ft_isdigit(*s))
// 			return (false);
// 		s++;
// 	}
// 	return (true);
// }

bool	ft_ispositivenbr(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (*s == '-')
		return (false);
	if (*s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}
