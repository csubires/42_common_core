/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 07:39:28 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_uint	get_or_set_pixel(mlx_image_t *image, int v[2], t_uint color, int read)
{
	t_uint8	pixel;
	t_uint	tmp;

	if (read && v[0] < (int)image->width && v[1] < (int)image->height)
	{
		pixel = image->pixels + (v[1] * image->width + v[0]) * sizeof(t_uint);
		tmp = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
		return (tmp);
	}
	if (!read && v[0] > 0 && v[1] > 0 && v[0] < (int)image->width && \
v[1] < (int)image->height)
	{
		tmp = (v[1] * image->width + v[0]) * sizeof(int);
		image->pixels[tmp + 0] = (color >> 24) & 0xFF;
		image->pixels[tmp + 1] = (color >> 16) & 0xFF;
		image->pixels[tmp + 2] = (color >> 8) & 0xFF;
		image->pixels[tmp + 3] = color & 0xFF;
	}
	return (0);
}

void	draw_textured_line(t_cub3d *cub3d, t_raycast *ray, \
double step, double index)
{
	t_uint	color;
	int		y;

	y = ray->line_start - 1;
	while (++y <= ray->draw_end)
	{
		ray->wall.y = (int)index & (cub3d->map->no->height - 1);
		color = get_or_set_pixel(ray->texture, \
(int []){ray->wall.x, ray->wall.y}, 0, 1);
		get_or_set_pixel(cub3d->img, (int []){cub3d->img->width \
- 1 - ray->x, y}, color, 0);
		index += step;
	}
}

static void	ray_init(t_cub3d *cub3d, t_raycast *ray)
{
	double	center_x;
	double	aspect_ratio;
	double	fov_factor;
	double	length;

	aspect_ratio = (double)cub3d->img->width / (double)cub3d->img->height;
	fov_factor = tan(3.1415926535 / 15) * aspect_ratio;
	center_x = (2.0 * ray->x / (double)cub3d->img->width) - 1.0;
	center_x *= fov_factor;
	ray->direction.x = cub3d->player->direction.x + \
cub3d->player->camera.x * center_x;
	ray->direction.y = cub3d->player->direction.y + \
cub3d->player->camera.y * center_x;
	length = sqrt(ray->direction.x * ray->direction.x + ray->direction.y \
* ray->direction.y);
	ray->direction.x /= length;
	ray->direction.y /= length;
	ray->origin.x = (int)cub3d->player->position.x;
	ray->origin.y = (int)cub3d->player->position.y;
	ray->delta.x = fabs(1 / ray->direction.x);
	ray->delta.y = fabs(1 / ray->direction.y);
	ray->angle_fixed = cos(atan(center_x));
}

static void	dda_init(t_cub3d *cub3d, t_raycast *ray)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->destination.x = (cub3d->player->position.x - ray->origin.x) * \
ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->destination.x = (ray->origin.x + 1.0 - cub3d->player->position.x) \
* ray->delta.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->destination.y = (cub3d->player->position.y - ray->origin.y) \
* ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->destination.y = (ray->origin.y + 1.0 - cub3d->player->position.y) \
* ray->delta.y;
	}
}

void	dda_raycasting(t_cub3d *cub3d, t_raycast *ray)
{
	ray_init(cub3d, ray);
	dda_init(cub3d, ray);
	while (1)
	{
		if (ray->destination.x < ray->destination.y)
		{
			ray->destination.x += ray->delta.x;
			ray->origin.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->destination.y += ray->delta.y;
			ray->origin.y += ray->step.y;
			ray->side = 1;
		}
		if (cub3d->map->map[ray->origin.y][ray->origin.x] == '1')
			break ;
	}
}
