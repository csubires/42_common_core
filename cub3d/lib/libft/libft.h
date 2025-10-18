/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:20:00 by csubires          #+#    #+#             */
/*   Updated: 2025/05/02 11:49:46 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

//	FT_PRINTF.H
# include <stdarg.h>
# define STR_HEX_LO		"0123456789abcdef"
# define STR_HEX_UP		"0123456789ABCDEF"
# define STR_DEC		"0123456789"

//	GET_NEXT_LINE
# include <fcntl.h>
# define MAX_OPEN_FILES	64
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	2024
# endif

char	**ft_split(char *str, char *sep);
char	**ft_arrayjoin(char **old, char *new_str);
char	*ft_get_next_line(int fd);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strdup_from(char *line, int start);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strrev(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

long	ft_atoi(const char *str, int *error);
int		ft_isdigit(int c);
int		ft_isspace(char c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_printf(int fd, const char *s, ...);
int		ft_putchar_fd(unsigned char c, int fd);
int		ft_putnbr_base(int fd, char c, unsigned long nbr, char *base);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strslen(char **s);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);

void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_free_ptr(char **ptr);
void	ft_free_array(char **array, int len);

#endif
