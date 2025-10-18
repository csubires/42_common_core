/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 10:12:03 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	initialize_mlx(t_cub3d *cub3d)
{
	int	width;
	int	height;

	cub3d->mlx = mlx_init(WIN_W, WIN_H, "CUB3D", true);
	if (!cub3d->mlx)
		free_all(ERR_MLX, 2, cub3d);
	cub3d->img = mlx_new_image(cub3d->mlx, WIN_W, WIN_H);
	if (!cub3d->img)
		free_all(ERR_MLX, 2, cub3d);
	mlx_set_setting(MLX_MAXIMIZED, MAXIMIZED);
	mlx_set_setting(MLX_DECORATED, DECORATED);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_pos(cub3d->mlx, (width - WIN_W) / 2, (height - WIN_H) / 2);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
		free_all(ERR_MLX, 2, cub3d);
}

static void	initialize_cub3d(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	map = (t_map *)malloc(sizeof(t_map));
	map->map_width = 0;
	map->map_height = 0;
	map->map = 0;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	cub3d->map = map;
	player = (t_player *)malloc(sizeof(t_player));
	player->position.x = 0;
	player->position.y = 0;
	player->number = 0;
	player->direction.x = -1;
	player->direction.y = 0;
	player->camera.x = 0;
	player->camera.y = 1;
	cub3d->player = player;
}

static void	mlx_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mlx_resize_image(cub3d->img, width, height);
	render(cub3d);
}

int	main(int argc, char *argv[])
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!cub3d)
		free_all(ERR_MALLOC, 2, cub3d);
	ft_printf(1, "\n %s[+]%s Loading MLX%s\n", CYAN, BLUE, ENDC);
	initialize_mlx(cub3d);
	ft_printf(1, " %s[+]%s Building CUB3D structure%s\n", CYAN, BLUE, ENDC);
	initialize_cub3d(cub3d);
	ft_printf(1, " %s[+]%s Validating extension%s\n", CYAN, BLUE, ENDC);
	parse_args(cub3d, argc, argv);
	ft_printf(1, " %s[+]%s Rendering raycast%s\n", CYAN, BLUE, ENDC);
	render(cub3d);
	ft_printf(1, "\n %s%s%s\n", GREEN, MSG_INITOK, ENDC);
	mlx_close_hook(cub3d->mlx, &close_window, cub3d);
	mlx_resize_hook(cub3d->mlx, &mlx_resize, cub3d);
	mlx_key_hook(cub3d->mlx, &key_hook, cub3d);
	mlx_loop(cub3d->mlx);
	free_all("", 0, cub3d);
	return (0);
}
