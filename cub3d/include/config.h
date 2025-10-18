/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:03:28 by csubires          #+#    #+#             */
/*   Updated: 2024/07/19 10:52:50 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define C_PI				3.14159265

# define MAXIMIZED			false
# define DECORATED			true
# define WIN_W				800
# define WIN_H				600
# define CUB_FIELDS			6
# define ROT_ANGLE			0.1
# define MOV_STEP			0.1
# define ALTITUDE			1.0

# define BLUE				"\e[1;34m"
# define GREEN				"\e[1;32m"
# define YELLOW				"\e[1;33m"
# define RED				"\e[1;31m"
# define MGENTA				"\e[1;35m"
# define CYAN				"\e[1;36m"
# define ENDC				"\e[1;0m"
# define CLEAR				"\e[2J\e[H"
# define RLINE				"\e[1A\e[K"

# define ERR_FILENOTOPEN	"Error\nFailed to open file"
# define ERR_EMPTYPATH		"Error\nNo path"
# define ERR_EXTENSION		"Error\nFile extension invalid"
# define ERR_FILENAME		"Error\nFile name invalid"
# define ERR_INVALIDCHAR	"Error\nForbidden character detected"
# define ERR_MALLOC			"Error\nMalloc error"
# define ERR_MLX			"Error\nCould not initialize MLX42"
# define ERR_MAPNOTCLOSED	"Error\nMap without close"
# define ERR_NOMAP			"Error\nMap format not valid"
# define ERR_CUB			"Error\nCub file format not valid"
# define ERR_BADNBRPLAYER	"Error\nThere must be only one player"
# define ERR_RGB			"Error\nColor rgb not valid"
# define ERR_TEXTUREEXT		"Error\nInvalid texture file"
# define ERR_INVALIDARGS	"Error\nIncorrect arguments\n\
							Use: ./cub3d maps/name_map.cub"
# define MSG_INITOK			"All ready. Press \
[W, S, A, D, or LEFT/RIGHT ARROWS]."

#endif
