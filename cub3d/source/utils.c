/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 11:15:26 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*fill_line(t_cub3d *cub3d, char *str)
{
	size_t	x;
	size_t	len;
	char	*tmp_str;

	if (!str || !cub3d->map->map_width)
	{
		ft_printf(1, ERR_MAPNOTCLOSED);
		return (0);
	}
	tmp_str = ft_calloc(cub3d->map->map_width + 1, sizeof(char));
	if (!tmp_str)
		free_all(ERR_MALLOC, 2, cub3d);
	x = 0;
	len = ft_strlen(str);
	while (x < len && str[x] && str[x] != '\n')
	{
		tmp_str[x] = str[x];
		x++;
	}
	while (x < cub3d->map->map_width)
		tmp_str[x++] = ' ';
	tmp_str[x] = '\0';
	return (tmp_str);
}

static void	delete_images(t_cub3d *cub3d)
{
	if (cub3d->map->no)
		mlx_delete_image(cub3d->mlx, cub3d->map->no);
	if (cub3d->map->so)
		mlx_delete_image(cub3d->mlx, cub3d->map->so);
	if (cub3d->map->we)
		mlx_delete_image(cub3d->mlx, cub3d->map->we);
	if (cub3d->map->ea)
		mlx_delete_image(cub3d->mlx, cub3d->map->ea);
	if (cub3d->img)
		mlx_delete_image(cub3d->mlx, cub3d->img);
}

void	free_all(char *str, int out, t_cub3d *cub3d)
{
	if (str)
		ft_printf(out, " %s%s%s\n", RED, str, ENDC);
	if (cub3d)
	{
		delete_images(cub3d);
		if (cub3d->map)
		{
			if (cub3d->map->map)
				ft_free_array(cub3d->map->map, -1);
			free(cub3d->map);
		}
		if (cub3d->player)
			free(cub3d->player);
		if (cub3d->fd_cub > 2)
			close(cub3d->fd_cub);
		if (cub3d->mlx)
			mlx_terminate(cub3d->mlx);
	}
	exit(0);
}
