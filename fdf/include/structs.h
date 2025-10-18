/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:39:36 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 10:10:56 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

// POINT
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

// VARS FOR A INSTANCE OF PROGRAM
typedef struct s_fdfs
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
}	t_fdfs;

#endif
