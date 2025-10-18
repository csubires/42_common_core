/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:29:06 by csubires          #+#    #+#             */
/*   Updated: 2024/11/25 11:28:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strconcat(int num_of_str, ...);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strltrim(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		ft_fdprint(int fd, char *format, ...);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_isallalpha(char *str);

#endif
