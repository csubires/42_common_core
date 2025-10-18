/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:12:11 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:39:28 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_vertical_line(t_cub3d *cub3d, t_raycast *ray)
{
	ray->line_height = (int)(cub3d->img->height / ray->final_distance);
	ray->line_start = -ray->line_height / 2 + cub3d->img->height / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->draw_end = ray->line_height / 2 + (int)cub3d->img->height / 2;
	if (ray->draw_end >= (int)cub3d->img->height)
		ray->draw_end = cub3d->img->height - 1;
}

static void	get_ray_texture(t_cub3d *cub3d, t_raycast *ray)
{
	if (ray->origin.x >= cub3d->player->position.x && !ray->side)
		ray->texture = cub3d->map->ea;
	if (ray->origin.x < cub3d->player->position.x && !ray->side)
		ray->texture = cub3d->map->we;
	if (ray->origin.y >= cub3d->player->position.y && ray->side)
		ray->texture = cub3d->map->so;
	if (ray->origin.y < cub3d->player->position.y && ray->side)
		ray->texture = cub3d->map->no;
}

static void	paint_ceil_and_floor(t_cub3d *cub3d, t_raycast *ray)
{
	int	y;

	y = -1;
	while (++y < ray->line_start)
		get_or_set_pixel(cub3d->img, (int []){cub3d->img->width \
- 1 - ray->x, y}, cub3d->map->rgb_ceiling, 0);
	y = ray->draw_end;
	while (++y < (int)cub3d->img->height)
		get_or_set_pixel(cub3d->img, (int []){cub3d->img->width \
- 1 - ray->x, y}, cub3d->map->rgb_floor, 0);
}

static void	paint_line_texture(t_cub3d *cub3d, t_raycast *ray)
{
	double	step;
	double	index;
	double	temp;

	if (ray->texture)
	{
		if (!ray->side)
			temp = cub3d->player->position.y + ray->final_distance \
* ray->direction.y;
		else
			temp = cub3d->player->position.x + ray->final_distance \
* ray->direction.x;
		temp -= floor((temp));
		ray->wall.x = (int)(temp * (double)(ray->texture->width));
		step = ALTITUDE * ray->texture->height / ray->line_height;
		index = (ray->line_start - cub3d->img->height / 2 + \
ray->line_height / 2) * step;
		draw_textured_line(cub3d, ray, step, index);
	}
}

void	render(t_cub3d *cub3d)
{
	t_raycast	ray;

	ray.x = cub3d->img->width;
	while (--ray.x >= 0)
	{
		dda_raycasting(cub3d, &ray);
		if (!ray.side)
			ray.final_distance = (ray.destination.x - ray.delta.x) \
* ray.angle_fixed;
		else
			ray.final_distance = (ray.destination.y - ray.delta.y) \
* ray.angle_fixed;
		get_vertical_line(cub3d, &ray);
		get_ray_texture(cub3d, &ray);
		paint_line_texture(cub3d, &ray);
		paint_ceil_and_floor(cub3d, &ray);
	}
}
