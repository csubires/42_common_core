/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 09:59:46 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <math.h>
# include <stdlib.h>
# include <time.h>
# include "config_bonus.h"
# include "structs_bonus.h"
# include "keys_bonus.h"
# include "colors_bonus.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

// COLOR_BONUS.C
int		get_color(t_point start, t_point end, t_point current, t_point delta);
int		generate_color(t_fdfs *fdfs, int cur_z);
// COLOR_UTILS_BONUS.C
void	set_palette(t_palette *palette, int selected);
// KEYS_BONUS.C
int		key_event(int keycode, t_fdfs *fdfs);
// MAIN_BONUS.C
int		close_win(t_fdfs *fdfs);
// MAP_BONUS.C
void	free_map(t_map *map);
void	set_z_limits(t_map *map);
void	create_struct_mem(t_map *map);
t_map	*initialise_map(char *file);
// PARSE_BONUS.C
void	parse_args(t_map **map, int argc, char *argv[]);
// RENDER_BONUS.C
int		render_menu(t_fdfs *fdfs, int width, int height);
void	show_menu(t_fdfs *fdfs);
void	render_map(t_fdfs *fdfs);
// RENDER_UTILS_BONUS.C
void	error_and_exit(const char *err, const char *msg);
void	rotate_x(t_fdfs *fdfs, int *y, int *z);
void	rotate_y(t_fdfs *fdfs, int *x, int *z);
void	rotate_z(t_fdfs *fdfs, int *x, int *y);
void	set_pixel(t_img *img, int x, int y, int color);
// UTILS_BONUS.C
void	free_all(t_fdfs *fdfs);
void	isometric(t_fdfs *fdfs, int *x, int *y, int z);
t_point	new_point(int x, int y, t_fdfs *fdfs);
t_point	get_coordinate(t_fdfs *fdfs, t_point point);
void	reset_fdfs(t_fdfs *fdfs);

#endif
