/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 12:02:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map)
{
	int	x;

	x = 0;
	if (!map || !*map)
		return (ft_printf(1, ERR_NOMAP), (void)0);
	ft_printf(1, "\n");
	while (map[x])
		ft_printf(1, "\t|%s|\n", map[x++]);
	ft_printf(1, "\n");
}

static char	**add_line(t_cub3d *cub3d, char **map, char *line)
{
	char	**temp;

	if (ft_strlen(line) > cub3d->map->map_width)
		cub3d->map->map_width = ft_strlen(line) - 1;
	temp = ft_arrayjoin(map, line);
	if (!temp)
		free_all(ERR_MALLOC, 2, cub3d);
	return (temp);
}

static char	*init_map(t_cub3d *cub3d)
{
	char	*current_line;

	current_line = ft_get_next_line(cub3d->fd_cub);
	while (current_line && current_line[0] == '\n')
	{
		free(current_line);
		current_line = ft_get_next_line(cub3d->fd_cub);
	}
	if (!current_line)
		free_all(ERR_NOMAP, 2, cub3d);
	return (current_line);
}

void	load_map(t_cub3d *cub3d)
{
	char	**map;
	char	*current_line;
	char	**new_map;

	map = NULL;
	current_line = init_map(cub3d);
	while (current_line)
	{
		if (current_line[0] == '\n')
		{
			free(current_line);
			ft_free_array(map, -1);
			free_all(ERR_MAPNOTCLOSED, 2, cub3d);
		}
		new_map = add_line(cub3d, map, current_line);
		if (!new_map)
		{
			free(current_line);
			ft_free_array(map, -1);
			free_all(ERR_MALLOC, 2, cub3d);
		}
		map = new_map;
		current_line = ft_get_next_line(cub3d->fd_cub);
	}
	cub3d->map->map = map;
}
