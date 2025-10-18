/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:48:34 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 12:16:04 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(size_t len, char **arr_ptr)
{
	while (len-- > 0)
	{
		free(arr_ptr[len]);
		arr_ptr[len] = 0;
	}
	free(arr_ptr);
	arr_ptr = 0;
}

static size_t	ft_num_words(char *s, char c)
{
	size_t	num;
	size_t	x;

	x = 0;
	num = 0;
	while (s[x])
	{
		if (s[x] != c)
		{
			num++;
			while (s[x] && s[x] != c)
				x++;
		}
		else if (s[x] == c)
			x++;
	}
	return (num);
}

static size_t	get_word_len(char *s, char c)
{
	size_t	x;

	x = 0;
	while (s[x] && s[x] != c)
		x++;
	return (x);
}

static char	**ft_cut_words(char *s, char c, char **arr_ptr, int num_words)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < num_words)
	{
		while (s[y] && s[y] == c)
			y++;
		arr_ptr[x] = ft_substr(s, y, get_word_len(&s[y], c));
		if (!arr_ptr[x])
		{
			ft_free(x, arr_ptr);
			return (0);
		}
		while (s[y] && s[y] != c)
			y++;
		x++;
	}
	arr_ptr[x] = 0;
	return (arr_ptr);
}

char	**ft_split(char *s, char c)
{
	char	**arr_ptr;
	size_t	num_words;

	if (!s)
		return (0);
	num_words = ft_num_words(s, c);
	arr_ptr = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!arr_ptr)
		return (0);
	arr_ptr = ft_cut_words(s, c, arr_ptr, num_words);
	return (arr_ptr);
}
