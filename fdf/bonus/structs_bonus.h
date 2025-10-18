/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:39:36 by csubires          #+#    #+#             */
/*   Updated: 2024/08/17 11:27:13 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

// MAP FILE
typedef struct s_map
{
	int	width;
	int	height;
	int	has_color;
	int	**color_file;
	int	**z_gen;
	int	min_z;
	int	max_z;
}	t_map;

// MAP IMAGE & MENU
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sz_l;
	int		endian;
}	t_img;

// SET COLORS FOR MAP
typedef struct s_palette
{
	int	color_1;
	int	color_2;
	int	color_3;
	int	color_4;
	int	color_5;
	int	color_6;
	int	color_7;
	int	color_8;
}	t_palette;

// OPTIONS OF PROGRAM
typedef struct s_state
{
	int			rnd_color;
	int			map_color;
	int			zenith;
	int			menu;
	t_palette	palette;
}	t_requirement;

// POINT
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

// VARS FOR A INSTANCE OF PROGRAM
typedef struct s_fdfs
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
	t_img	*menu;
	int		step_x;
	int		step_y;
	float	rotate_x;
	float	rotate_y;
	float	rotate_z;
	t_requirement	state;
	float	zoom;
	float	flat;
}	t_fdfs;

#endif
