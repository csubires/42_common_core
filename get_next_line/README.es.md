![Rating](/assets/images/header.png)

# GET_NEXT_LINE

<table align="center">
<caption>Tabla de contenidos</caption>
<tbody>
<tr><td align="center"><b>

[GET_NEXT_LINE](#DESCRIPCIÓN)

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

- [Referencias](#referencias)
- [Glosario](#glosario)

---

### DESCRIPCIÓN

El objetivo de este proyecto es simple: programar una función que devuelva una línea leída de un file descriptor.


### Restricciones

- Debe compilarse con `gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 files.c`
- No se permite lseek
- Tener en cuenta los `\n`
- Variables globales prohibidas
- Bonus:
	- Pasar con 1 sola static variable
	- Leer varios ficheros a la vez sin perder el hilo

## get_next_line.c
``` c
static char	*ft_cut_line(char *buffer_global)
```
Devuelte una línea del buffer global. Recorre el buffer contando la longitud hasta encontrar un salto de línea. Reserva memoria con esa longitud (+1, \0), utiliza ft_strlcpy para copiar la línea y la devuelve.

### ft_cut_remainder
``` c
static char	*ft_cut_remainder(char *buffer_global)
```
Una vez devuelta la línea queda un resto que no puede perderse. Para evitarlo la función hace algo parecido a ft_cut_line con la diferencia de que devolverá el resto de la cadena a partir del salto de línea.

### ft_fill_buffer
``` c
static char	*ft_fill_buffer(int fd, char *buffer_global)
```
Función que rellena el buffer (ft_strjoin) leyendo el archivo mientras no se detecte un salto de línea. Si hay cualquier error la función libera todos los buffer y retornará un NULL.

## get_next_line
``` c
char	*get_next_line(int fd)
```
LLamar a rellenar el buffer global, si todo va bien, llama a cortar una línea, guardar el resto, y devolver la línea.

## get_next_line_utils.c

### ft_freeme
``` c
void	ft_freeme(char **ptr);
```
Simplemente una función para liberar memoria y poder pasar la norma.

### ft_strlen
``` c
size_t	ft_strlen(const char *s);
```
Función del ft_libft para obtener el tamaño de una cadena (string [char *str]).

### ft_strlcpy
``` c
size_t	ft_strlcpy(char *dst, const char *src,
size_t dstsize);
```
Función del ft_libft usada para copiar el contenido de una línea, o en el caso de devolver el resto del buffer no devuelto.

### ft_strchr
``` c
char	*ft_strchr(const char *s, int c);
```
Función del ft_libft para encontrar el caracter del salto de línea (\n) en el buffer devuelto por __read__.

### ft_strjoin
``` c
char	*ft_strjoin(char *s1, char *s2);
```
Función del ft_libft para unir los trozos de buffer leidos por el __read__ y que no se han devuelto si no encuentra el caracter de salto de línea (\n).
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## BONUS

## get_next_line_bonus
``` c
char	*get_next_line_bonus(int fd);
```
El bonus consiste en leer más de un archivo a la vez. Esto se consige fácilmente convirtiendo la variable estatica del buffer global en un array de variables estaticos de buffers globales y asignando cada fd (descriptor del archivo o id) a una de las posiciones de dicho array. Y a la hora de utilizar un fs distinto se trabajará con la posición especifica del array-buffer para ese fs.

### get_next_line_utils_bonus
Se utilizan las mismas funciones que para la parte obligatoria.

<div style='text-align: right;'>

[UP &#11014;](#get_next_line)
</div>

## Referencias
https://42.nauman.cc/category/cursus/get_next_line

## Glosario

- fd: File Descriptor

[
	$${\color{red}VOLVER}$$
](../../README.md)
