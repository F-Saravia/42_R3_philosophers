/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasaravi <fasaravi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:37:16 by fasaravi          #+#    #+#             */
/*   Updated: 2026/09/19 18:28:04 by fasaravi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(int fd, char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	write(fd, s, l);
}

void	ft_puts_fd(int fd, char *s)
{
	ft_putstr_fd(fd, s);
	write(fd, "\n", 1);
}

static void	ft_putnbr_fd_digits(int fd, long number)
{
	char	c;

	if (number >= 10 || number <= -10)
		ft_putnbr_fd_digits(fd, (number / 10));
	number %= 10;
	if (number < 0)
		number *= -1;
	c = number + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int fd, long number)
{
	if (number < 0)
		write(fd, "-", 1);
	ft_putnbr_fd_digits(fd, number);
}

void	print_philo_isdoing(long timestamp, int phid, char *doing)
{
	ft_putnbr_fd(STDOUT_FILENO, timestamp);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(STDOUT_FILENO, (long) phid);
	write(STDOUT_FILENO, " ", 1);
	ft_puts_fd(STDOUT_FILENO, doing);
}
