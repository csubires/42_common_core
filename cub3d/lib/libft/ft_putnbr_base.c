/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:09 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:27:22 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_validate_base(char *str)
{
	unsigned int	valid;
	unsigned int	len_base;
	unsigned int	y;

	valid = 1;
	len_base = 0;
	if (str[0] == '\0')
		return (0);
	while (str[len_base] && valid)
	{
		if (ft_isspace(str[len_base]) || \
str[len_base] == '+' || str[len_base] == '-')
			valid = 0;
		y = 0;
		while (str[len_base] != str[y] && y < len_base)
			y++;
		if (y != len_base)
			valid = 0;
		len_base++;
	}
	if (len_base <= 1 || !valid)
		return (0);
	return (len_base);
}

static int	ft_show_number(int fd, unsigned long nbr, char *base, \
unsigned int len)
{
	int	len_nbr;
	int	temp;

	if (nbr < len)
		return (ft_putchar_fd(base[nbr], fd));
	len_nbr = ft_show_number(fd, nbr / len, base, len);
	if (len_nbr == -1)
		return (-1);
	temp = ft_putchar_fd(base[nbr % len], fd);
	if (temp == -1)
		return (-1);
	return (len_nbr + temp);
}

int	ft_putnbr_base(int fd, char c, unsigned long nbr, char *base)
{
	unsigned int	len_base;
	int				len_print;
	int				temp;

	len_print = 0;
	if (c == 'p')
	{
		len_print = ft_putstr_fd("0x", fd);
		if (len_print == -1)
			return (-1);
	}
	if (!nbr)
		return (len_print + ft_putchar_fd('0', fd));
	len_base = ft_validate_base(base);
	if (len_base)
	{
		temp = ft_show_number(fd, nbr, base, len_base);
		if (temp == -1)
			return (-1);
		len_print += temp;
	}
	return (len_print);
}
