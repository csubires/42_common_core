/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/17 09:20:33 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	lambda(char *c)
{
	*c = ft_tolower(*c);
}

static int	parse_color(t_map *map, char *s)
{
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '+' || *s == ','))
		s++;
	if (*s && *s == 'x')
	{
		map->has_color = 1;
		ft_striter(s + 1, lambda);
		return (ft_atoi_base(s + 1, HEX_BASE));
	}
	else
		return (BG_COLOR);
	return (0);
}

static void	map_to_mem(t_map *map, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**split;
	int		error;

	y = -1;
	while (++y < map->height)
	{
		line = ft_get_next_line(fd);
		split = ft_split(line, ' ');
		if (!split)
		{
			free_map(map);
			error_and_exit("map_to_mem", "split = ft_split");
		}
		x = -1;
		while (++x < map->width)
		{
			map->z_gen[y][x] = ft_atoi_err(split[x], &error);
			map->color_file[y][x] = parse_color(map, split[x]);
		}
		ft_free_split(split);
		free(line);
	}
}

static void	parse_file(t_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		error_and_exit(file, "Error to open file or calloc.");
	}
	map_to_mem(map, fd);
	close(fd);
}

void	parse_args(t_map **map, int argc, char *argv[])
{
	if (argc != 2)
		error_and_exit(" Incorrect arguments", \
		"\nUse: ./fdf maps/name_map.fdf");
	ft_printf("\n Preparing map, wait...\n");
	ft_printf(" [+] Reading file fdf\n");
	*map = initialise_map(argv[1]);
	ft_printf(" [+] Creating the memory structure\n");
	create_struct_mem(*map);
	ft_printf(" [+] Loading map into memory\n");
	parse_file(*map, argv[1]);
	ft_printf(" [+] Obtaining isometric coordinates\n");
	set_z_limits(*map);
	ft_printf(" All ready. Press [ENTER] to open the help menu.\n");
}
