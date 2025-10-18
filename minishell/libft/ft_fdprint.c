/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:55:10 by csubires          #+#    #+#             */
/*   Updated: 2024/10/12 12:20:17 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd(int fd, int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(fd, n / 10);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static void	ft_puthex_fd(int fd, unsigned int n)
{
	char	*hex;
	char	c;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex_fd(fd, n / 16);
	c = hex[n % 16];
	write(fd, &c, 1);
}

static void	ft_putstr_fd(int fd, const char *str)
{
	while (str && *str)
		write(fd, str++, 1);
}

int	ft_handle_format(int fd, char c, va_list args)
{
	char	pc;

	if (c == 'd')
		ft_putnbr_fd(fd, va_arg(args, int));
	else if (c == 's')
		ft_putstr_fd(fd, va_arg(args, char *));
	else if (c == 'c')
	{
		pc = (char)va_arg(args, int);
		write(fd, &pc, 1);
	}
	else if (c == 'x')
		ft_puthex_fd(fd, va_arg(args, unsigned int));
	else
	{
		write(fd, &"%", 1);
		write(fd, &c, 1);
	}
	return (0);
}

int	ft_fdprint(int fd, char *format, ...)
{
	va_list	args;
	size_t	x;
	int		count;

	va_start(args, format);
	count = 0;
	x = 0;
	while (format[x])
	{
		if (format[x] == '%' && format[x + 1])
			ft_handle_format(fd, format[++x], args);
		else
			write(fd, &format[x], 1);
		x++;
	}
	va_end(args);
	return (count);
}
