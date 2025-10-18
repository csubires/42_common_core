/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:03:28 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 11:04:55 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_BONUS_H
# define CONFIG_BONUS_H

# define HEX_BASE		"0123456789abcdef"
# ifndef WIN_W
#  define WIN_W			1920
# endif
# ifndef WIN_W
#  define WIN_H			1080
# endif
// SPEED MOVES
# define STEP_MOVE		10
# define STEP_ROTATE	0.05
# define STEP_ZOOM		0.5
# define STEP_ALTITUDE	0.1
// GRADE
# define DEGREE_30		0.523599
# define DEGREE_45		0.785399
# define DEGREE_60		1.047197

#endif
