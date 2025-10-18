/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 10:10:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "../include/config.h"
# include "../include/structs.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

// MAP.C
void	free_map(t_map *map);
void	set_z_limits(t_map *map);
void	create_struct_mem(t_map *map);
t_map	*initialise_map(char *file);
// PARSE.C
void	parse_args(t_map **map, int argc, char *argv[]);
// RENDER.C
void	render_map(t_fdfs *fdfs);
// UTILS.C
void	error_and_exit(const char *msg);
void	free_all(t_fdfs *fdfs);
t_point	new_point(int x, int y, t_fdfs *fdfs);
t_point	get_coordinate(t_fdfs *fdfs, t_point point);

#endif
