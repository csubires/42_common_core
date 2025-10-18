/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:57:33 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 10:49:08 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

# define STR_HEX_LO	"0123456789abcdef"
# define STR_HEX_UP	"0123456789ABCDEF"
# define STR_DEC	"0123456789"

// FT_PRINTF.C
int		ft_printf(char const *s, ...);

#endif
