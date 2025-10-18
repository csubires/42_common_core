/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:45:35 by csubires          #+#    #+#             */
/*   Updated: 2024/11/16 12:56:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(int n, ...)
{
	va_list		args;
	char		*str;
	char		*join;
	char		*tmp_join;

	if (n <= 0)
		return (0);
	va_start(args, n);
	join = ft_strdup("");
	while (n--)
	{
		str = va_arg(args, char *);
		if (str)
		{
			tmp_join = ft_strjoin(join, str);
			free(join);
			join = tmp_join;
		}
	}
	va_end(args);
	return (join);
}
