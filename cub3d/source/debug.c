/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/10 08:43:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void print_map(char **map)
{
	int x;

	x = 0;
	if (!map || !*map)
	{
		ft_printf(1, "\n NOOOO MAP!!!!\n");
		return ;
	}
	ft_printf(1, "\nMAP:\n");
	while (map[x])
		ft_printf(1, "\t%s\n", map[x++]);
}


void print_cub3d(t_cub3d *cub3d)
{

	ft_printf(1, "\nCUB3D\n");

	ft_printf(1, "\tcub3d->map: %d\n", cub3d->map);
	ft_printf(1, "\tcub3d->player: %d\n", cub3d->player);
	ft_printf(1, "\tcub3d->mlx: %d\n", cub3d->mlx);
	ft_printf(1, "\tcub3d->img: %d\n", cub3d->img);
	ft_printf(1, "\tcub3d->time: %ld\n", cub3d->time);
	ft_printf(1, "\tcub3d->width: %dpx\n", cub3d->width);
	ft_printf(1, "\tcub3d->height: %dpx\n", cub3d->height);
	ft_printf(1, "\tcub3d->fd_cub: %d\n", cub3d->fd_cub);

	ft_printf(1, "\nMAP STRUCT\n");

	ft_printf(1, "\tcub3d->map: %d\n", cub3d->map);
	ft_printf(1, "\tcub3d->map->no: %d\n", cub3d->map->no);
	ft_printf(1, "\tcub3d->map->so: %d\n", cub3d->map->so);
	ft_printf(1, "\tcub3d->map->we: %d\n", cub3d->map->we);
	ft_printf(1, "\tcub3d->map->ea: %d\n", cub3d->map->ea);
	ft_printf(1, "\tcub3d->map->rgb_bottom: %d\n", cub3d->map->rgb_bottom);
	ft_printf(1, "\tcub3d->map->rgb_top: %d\n", cub3d->map->rgb_top);
	ft_printf(1, "\tcub3d->map->len_width: %ld\n", cub3d->map->len_width);
	//ft_printfc1, ub3d->map->fc[2]: ("%d\n", cub3d->map->fc[2]);
	print_map(cub3d->map->map);

	ft_printf(1, "\nPLAYER\n");
}
