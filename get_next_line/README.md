![Rating](/assets/images/header.png)

# GET_NEXT_LINE

<table align="center">
<caption>Table of Contents</caption>
<tbody>
<tr><td align="center"><b>

[GET_NEXT_LINE](#DESCRIPTION)

</b></td><td align="center"><b>

[BONUS](#BONUS)</td></tr><tr><td>

0. [get_next_line](#get_next_line)
1. [get_next_line_utils](#get_next_line_utilsc)
</td><td>

2. [get_next_line_bonus](#get_next_line_bonus)
1. [get_next_line_utils_bonus](#get_next_line_utils_bonus)

</td></tr>
</tbody>
</table>

- [References](#references)
- [Glossary](#glossary)

---

### DESCRIPTION

The goal of this project is simple: program a function that returns a line read from a file descriptor.

### Restrictions

- Must compile with `gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 files.c`
- lseek is not allowed
- Consider `\n` characters
- Global variables prohibited
- Bonus:
	- Pass with only 1 static variable
	- Read multiple files at once without losing track

## get_next_line.c
``` c
static char	*ft_cut_line(char *buffer_global)
```
Returns a line from the global buffer. Traverses the buffer counting the length until it finds a newline character. Allocates memory with that length (+1, \0), uses ft_strlcpy to copy the line and returns it.

### ft_cut_remainder
``` c
static char	*ft_cut_remainder(char *buffer_global)
```
Once the line is returned, there remains a remainder that cannot be lost. To avoid this, the function does something similar to ft_cut_line with the difference that it will return the remainder of the string starting from the newline character.

### ft_fill_buffer
``` c
static char	*ft_fill_buffer(int fd, char *buffer_global)
```
Function that fills the buffer (ft_strjoin) by reading the file until a newline character is detected. If there is any error, the function frees all buffers and returns NULL.

## get_next_line
``` c
char	*get_next_line(int fd)
```
Calls to fill the global buffer, if everything goes well, calls to cut a line, save the remainder, and return the line.

## get_next_line_utils.c

### ft_freeme
``` c
void	ft_freeme(char **ptr);
```
Simply a function to free memory and be able to pass the norm.

### ft_strlen
``` c
size_t	ft_strlen(const char *s);
```
Function from ft_libft to get the size of a string (string [char *str]).

### ft_strlcpy
``` c
size_t	ft_strlcpy(char *dst, const char *src,
size_t dstsize);
```
Function from ft_libft used to copy the content of a line, or in the case of returning the unreturned remainder of the buffer.

### ft_strchr
``` c
char	*ft_strchr(const char *s, int c);
```
Function from ft_libft to find the newline character (\n) in the buffer returned by __read__.

### ft_strjoin
``` c
char	*ft_strjoin(char *s1, char *s2);
```
Function from ft_libft to join the buffer chunks read by __read__ that have not been returned if the newline character (\n) is not found.
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## BONUS

## get_next_line_bonus
``` c
char	*get_next_line_bonus(int fd);
```
The bonus consists of reading more than one file at a time. This is easily achieved by converting the static variable of the global buffer into an array of static global buffer variables and assigning each fd (file descriptor or id) to one of the positions in that array. And when using a different fd, it will work with the specific position of the array-buffer for that fd.

### get_next_line_utils_bonus
The same functions as the mandatory part are used.

<div style='text-align: right;'>

[UP &#11014;](#get_next_line)
</div>

## References
https://42.nauman.cc/category/cursus/get_next_line

## Glossary

- fd: File Descriptor

[$${\color{red}BACK}$$](../../README.md)
