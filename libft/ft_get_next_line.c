/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:36:05 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 18:20:26 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cut_line(char *buffer_global)
{
	int		x;
	char	*line;

	if (!buffer_global || !buffer_global[0])
		return (0);
	x = 0;
	while (buffer_global[x] && buffer_global[x] != '\n')
		x++;
	if (!buffer_global[x])
		x--;
	line = (char *)malloc(sizeof(char) * (x + 2));
	if (!line)
		return (0);
	if (!ft_strlcpy(line, buffer_global, x + 2))
	{
		ft_free_ptr(&buffer_global);
		ft_free_ptr(&line);
	}
	return (line);
}

static char	*ft_cut_remainder(char *buffer_global)
{
	char			*remainder;
	char			*tmp_buffer_global;
	unsigned int	len_remainder;

	tmp_buffer_global = buffer_global;
	while (*tmp_buffer_global && *tmp_buffer_global != '\n')
		tmp_buffer_global++;
	if (!*tmp_buffer_global)
	{
		ft_free_ptr(&buffer_global);
		return (0);
	}
	tmp_buffer_global++;
	len_remainder = ft_strlen(tmp_buffer_global);
	remainder = (char *)malloc(sizeof(char) * (len_remainder + 1));
	if (!remainder)
	{
		ft_free_ptr(&buffer_global);
		return (0);
	}
	if (!ft_strlcpy(remainder, tmp_buffer_global, len_remainder + 1))
		ft_free_ptr(&remainder);
	ft_free_ptr(&buffer_global);
	return (remainder);
}

static char	*ft_fill_buffer(int fd, char *buffer_global)
{
	char	*buffer_read;
	int		len_read;

	buffer_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_read)
		return (0);
	len_read = 1;
	while (len_read && !ft_strchr(buffer_global, '\n'))
	{
		len_read = read(fd, buffer_read, BUFFER_SIZE);
		if (len_read == -1)
		{
			ft_free_ptr(&buffer_global);
			ft_free_ptr(&buffer_read);
			return (0);
		}
		buffer_read[len_read] = '\0';
		buffer_global = ft_strjoin(buffer_global, buffer_read);
	}
	ft_free_ptr(&buffer_read);
	return (buffer_global);
}

char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	*buffer_global[MAX_OPEN_FILES];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_OPEN_FILES)
		return (0);
	buffer_global[fd] = ft_fill_buffer(fd, buffer_global[fd]);
	if (!buffer_global[fd])
	{
		ft_free_ptr(&buffer_global[fd]);
		buffer_global[fd] = 0;
		return (0);
	}
	line = ft_cut_line(buffer_global[fd]);
	buffer_global[fd] = ft_cut_remainder(buffer_global[fd]);
	return (line);
}
