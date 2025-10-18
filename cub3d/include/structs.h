/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:39:36 by csubires          #+#    #+#             */
/*   Updated: 2024/07/16 12:58:47 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef unsigned int	t_uint;
typedef unsigned char*	t_uint8;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_vector
{
	double			x;
	double			y;
}	t_vector;

typedef struct s_map
{
	char			**map;
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	int				rgb_ceiling;
	int				rgb_floor;
	size_t			map_width;
	size_t			map_height;
}	t_map;

typedef struct s_player
{
	t_vector		position;
	t_vector		camera;
	t_vector		direction;
	size_t			number;
}	t_player;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_map			*map;
	t_player		*player;
	mlx_image_t		*img;
	int				fd_cub;
}	t_cub3d;

typedef struct s_raycast
{
	int				line_start;
	int				draw_end;
	int				line_height;
	t_vector		wall;
	t_vector		destination;
	t_int_vector	origin;
	t_vector		step;
	int				side;
	int				x;
	int				y;
	t_vector		direction;
	t_vector		delta;
	double			final_distance;
	double			angle_fixed;
	mlx_image_t		*texture;
}	t_raycast;

#endif
