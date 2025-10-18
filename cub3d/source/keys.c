/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 09:49:04 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	close_window(void *param)
{
	free_all("", 1, (t_cub3d *)param);
}

static void	rotate(t_vector *vector, double step)
{
	double	pre_x;
	double	pre_y;

	pre_x = vector->x;
	pre_y = vector->y;
	vector->x = pre_x * cos(step) - pre_y * sin(step);
	vector->y = pre_x * sin(step) + pre_y * cos(step);
}

static void	move(t_cub3d *cub3d, double step, t_vector vector)
{
	t_vector	pos;
	int			sign;
	char		**map;
	int			tmp;

	sign = 0;
	map = cub3d->map->map;
	pos = cub3d->player->position;
	if (fabs(vector.x) == 1)
		sign = vector.x;
	tmp = (int)(pos.x + vector.x * step * 2);
	if (map[(int)(pos.y + sign * 0.1)][tmp] == '0' && \
map[(int)(pos.y - sign * 0.1)][tmp] == '0')
		cub3d->player->position.x += vector.x * step;
	if (fabs(vector.y) == 1)
		sign = vector.y;
	tmp = (int)(pos.y + vector.y * step * 2);
	if (map[tmp][(int)(pos.x + sign * 0.1)] == '0' && \
map[tmp][(int)(pos.x - sign * 0.1)] == '0')
		cub3d->player->position.y += vector.y * step;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		free_all("", 1, cub3d);
	else if (keydata.key == MLX_KEY_LEFT)
	{
		rotate(&cub3d->player->direction, -ROT_ANGLE);
		rotate(&cub3d->player->camera, -ROT_ANGLE);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		rotate(&cub3d->player->direction, ROT_ANGLE);
		rotate(&cub3d->player->camera, ROT_ANGLE);
	}
	else if (keydata.key == MLX_KEY_W)
		move(cub3d, MOV_STEP, cub3d->player->direction);
	else if (keydata.key == MLX_KEY_S)
		move(cub3d, -MOV_STEP, cub3d->player->direction);
	else if (keydata.key == MLX_KEY_A)
		move(cub3d, MOV_STEP, cub3d->player->camera);
	else if (keydata.key == MLX_KEY_D)
		move(cub3d, -MOV_STEP, cub3d->player->camera);
	render(cub3d);
}
