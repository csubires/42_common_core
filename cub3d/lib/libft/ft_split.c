/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:17:46 by csubires          #+#    #+#             */
/*   Updated: 2025/01/10 11:29:00 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_is_sep(char c, char *sep)
{
	int	x;

	x = 0;
	while (sep[x])
	{
		if (sep[x] == c)
			return (1);
		x++;
	}
	return (0);
}

static int	split_count(char *str, char *sep)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	while (str[x])
	{
		while (str[x] && split_is_sep(str[x], sep))
			x++;
		if (str[x])
			len++;
		while (str[x] && !split_is_sep(str[x], sep))
			x++;
	}
	return (len);
}

static int	split_size(char *str, char *sep)
{
	int	x;

	x = 0;
	while (str[x] && !split_is_sep(str[x], sep))
		x++;
	return (x);
}

char	**ft_split(char *str, char *sep)
{
	char	**array;
	char	*word;
	int		x;

	array = (char **)malloc(sizeof(char *) * (split_count(str, sep) + 1));
	x = 0;
	if (!array)
		return (0);
	while (*str)
	{
		while (*str && split_is_sep(*str, sep))
			str++;
		if (!(*str))
			break ;
		word = ft_substr(str, 0, split_size(str, sep));
		if (!word)
			return (ft_free_array(array, x), (void *)0);
		while (*str && !split_is_sep(*str, sep))
			str++;
		array[x++] = word;
	}
	array[x] = 0;
	return (array);
}
