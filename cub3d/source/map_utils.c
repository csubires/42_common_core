/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:08:11 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:39:28 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player(t_cub3d *cub3d, double coordinates[4])
{
	cub3d->player->number++;
	cub3d->player->direction.x = coordinates[0];
	cub3d->player->direction.y = coordinates[2];
	cub3d->player->camera.x = coordinates[1];
	cub3d->player->camera.y = coordinates[3];
}

static void	check_char(t_cub3d *cub3d, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cub3d->player->position.x = x + 0.5f;
		cub3d->player->position.y = y + 0.5f;
		cub3d->map->map[y][x] = '0';
		if (c == 'N')
			set_player(cub3d, (double []){0, -1, -1, 0});
		else if (c == 'S')
			set_player(cub3d, (double []){0, 1, 1, 0});
		else if (c == 'E')
			set_player(cub3d, (double []){1, 0, 0, -1});
		else if (c == 'W')
			set_player(cub3d, (double []){-1, 0, 0, 1});
	}
	else if (c != '0' && c != '1' && c != ' ')
		free_all(ERR_INVALIDCHAR, 2, cub3d);
}

static void	check_position(t_cub3d *cub3d, int x, size_t y)
{
	if (y == 0 || y == cub3d->map->map_width - 1 || \
x == 0 || x == ft_strslen(cub3d->map->map) - 1)
	{
		free_all(ERR_MAPNOTCLOSED, 2, cub3d);
	}
	if (x > 0 && x < ft_strslen(cub3d->map->map) - 1 && \
y > 0 && y < cub3d->map->map_width - 1)
	{
		if (cub3d->map->map[x - 1][y] == ' ' || \
cub3d->map->map[x + 1][y] == ' ' || \
cub3d->map->map[x][y - 1] == ' ' || \
cub3d->map->map[x][y + 1] == ' ')
		{
			free_all(ERR_MAPNOTCLOSED, 2, cub3d);
		}
	}
	else
	{
		free_all(ERR_MAPNOTCLOSED, 2, cub3d);
	}
}

static void	check_line(char *line, t_cub3d *cub3d, int x)
{
	size_t	y;

	y = 0;
	while (line[y])
	{
		check_char(cub3d, line[y], x, y);
		if (line[y] == '0' || line[y] == 'N' || line[y] == 'S' || \
line[y] == 'W' || line[y] == 'E')
			check_position(cub3d, x, y);
		y++;
	}
}

void	check_map(t_cub3d *cub3d)
{
	int		x;
	char	*tmp;

	if (!cub3d->map->map)
		free_all(ERR_NOMAP, 2, cub3d);
	x = 0;
	while (cub3d->map->map[x])
	{
		tmp = cub3d->map->map[x];
		cub3d->map->map[x] = fill_line(cub3d, tmp);
		free(tmp);
		x++;
	}
	x = 0;
	while (cub3d->map->map[x])
	{
		check_line(cub3d->map->map[x], cub3d, x);
		x++;
	}
	cub3d->map->map_height = x;
	if (!cub3d->player->number || cub3d->player->number > 1)
		free_all(ERR_BADNBRPLAYER, 2, cub3d);
}
