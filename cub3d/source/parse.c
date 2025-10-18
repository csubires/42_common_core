/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/05 09:08:25 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static mlx_image_t	*load_asset(t_cub3d *cub3d, char *line, int start)
{
	mlx_texture_t	*asset;
	mlx_image_t		*img;
	char			*path;

	if (ft_strlen(line) - start == 1)
		return (free_all(ERR_EMPTYPATH, 2, cub3d), (void *)0);
	path = ft_strdup_from(line, start);
	asset = mlx_load_png(path);
	free(path);
	if (!asset)
		return (free(line), free_all(ERR_TEXTUREEXT, \
2, cub3d), (void *)0);
	img = mlx_texture_to_image(cub3d->mlx, asset);
	mlx_delete_texture(asset);
	if (!img)
		return (free(line), free_all(ERR_TEXTUREEXT, 2, cub3d), (void *)0);
	return (img);
}

static int	load_color(t_cub3d *cub3d, char *line)
{
	int		rgb[3];
	char	**col;
	int		x;
	int		error;

	col = ft_split(line, " ,\n");
	if (!col)
		return (free(line), free_all(ERR_RGB, 2, cub3d), 1);
	if (ft_strslen(col) != 4)
	{
		ft_free_array(col, -1);
		free(line);
		free_all(ERR_RGB, 2, cub3d);
		return (1);
	}
	x = -1;
	while (++x < 3)
	{
		rgb[x] = ft_atoi(col[x + 1], &error);
		if (ft_strlen(col[x + 1]) > 3 || rgb[x] > 255 || rgb[x] < 0)
			return (ft_free_array(col, -1), free(line), \
free_all(ERR_RGB, 2, cub3d), 1);
	}
	ft_free_array(col, -1);
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF);
}

static int	analyze_line(t_cub3d *cub3d, t_map *map, char *line, int nfields)
{
	int	not_found;

	not_found = 1;
	if (line && line[0] == '\n')
		return (nfields);
	else if (!ft_strncmp(line, "NO ", 3))
		map->no = load_asset(cub3d, line, 3);
	else if (!ft_strncmp(line, "SO ", 3))
		map->so = load_asset(cub3d, line, 3);
	else if (!ft_strncmp(line, "WE ", 3))
		map->we = load_asset(cub3d, line, 3);
	else if (!ft_strncmp(line, "EA ", 3))
		map->ea = load_asset(cub3d, line, 3);
	else if (!ft_strncmp(line, "F ", 2))
		map->rgb_floor = load_color(cub3d, line);
	else if (!ft_strncmp(line, "C ", 2))
		map->rgb_ceiling = load_color(cub3d, line);
	else
		not_found = 0;
	if (not_found)
		ft_printf(1, "\t[%d] %s%s%s", \
++nfields, YELLOW, line, ENDC);
	return (nfields);
}

static void	fill_struct(t_cub3d *cub3d)
{
	char	*line;
	int		nfields;

	nfields = 0;
	while (nfields != CUB_FIELDS)
	{
		line = ft_get_next_line(cub3d->fd_cub);
		if (!line)
			break ;
		if (line[0] != '\n')
			nfields = analyze_line(cub3d, cub3d->map, line, nfields);
		free(line);
	}
	if (nfields != CUB_FIELDS)
		free_all(ERR_CUB, 2, cub3d);
	ft_printf(1, " %s[+]%s Reading map%s\n", CYAN, BLUE, ENDC);
	load_map(cub3d);
}

void	parse_args(t_cub3d	*cub3d, int argc, char *argv[])
{
	if (argc != 2)
		free_all(ERR_INVALIDARGS, 2, cub3d);
	if (ft_strlen(argv[1]) < 5)
		free_all(ERR_FILENAME, 2, cub3d);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		free_all(ERR_EXTENSION, 2, cub3d);
	ft_printf(1, " %s[+]%s Parsing cub file%s\n", CYAN, BLUE, ENDC);
	cub3d->fd_cub = open(argv[1], O_RDONLY);
	if (cub3d->fd_cub < 0)
		free_all(ERR_FILENOTOPEN, 2, cub3d);
	ft_printf(1, " %s[+]%s Filling structures%s\n", CYAN, BLUE, ENDC);
	fill_struct(cub3d);
	close(cub3d->fd_cub);
	ft_printf(1, " %s[+]%s Checking map%s\n", CYAN, BLUE, ENDC);
	check_map(cub3d);
	print_map(cub3d->map->map);
}
