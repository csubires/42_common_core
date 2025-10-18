/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/19 13:11:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "./structs.h"
# include "./config.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

//		 KEYS.C
void	close_window(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);

//		MAIN.C
int		main(int argc, char *argv[]);

//		MAP_UTILS.C
void	check_map(t_cub3d *cub3d);

//		MAP.C
void	load_map(t_cub3d *cub3d);
void	print_map(char **map);

//		PARSE.C
void	parse_args(t_cub3d	*cub3d, int argc, char *argv[]);

//		RENDER_UTILS.C
t_uint	get_or_set_pixel(mlx_image_t *image, int v[2], t_uint color, int read);
void	draw_textured_line(t_cub3d *cub3d, t_raycast *ray, \
double step, double index);
void	dda_raycasting(t_cub3d *cub3d, t_raycast *ray);

//		RENDER.C
void	render(t_cub3d *cub3d);

//		UTILS.C
char	*fill_line(t_cub3d *cub3d, char *str);
void	free_all(char *str, int out, t_cub3d *cub3d);

#endif
