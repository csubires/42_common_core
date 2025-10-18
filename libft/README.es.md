![Rating](/assets/images/header.png)

# LIBFT

>[!NOTE]
>LA LIBRERÍA HA SIDO MODIFICADA AÑADIENDO NUEVAS FUNCIONES Y MODIFICANDO ALGUNAS FUNCIONES EXISTENTES, CON LO CUAL NO PASARÍA LA MOULINETTE. PARA VER LAS FUNCIONES ORIGINALES QUE ENTREGÉ EN LA PLATAFORMA, VER [LIBFT ORIGINAL](./../../libft_original/)

<table align="center">
<caption>Tabla de contenidos</caption>
<tbody>
<tr><td align="center"><b>

[LIBFT](#LIBFT)</b></td>
    <td align="center"><b>
[ADICIONAL](#ADICIONAL)</td>
    <td align="center"><b>
[BONUS](#BONUS)</td>
    <td align="center"><b>
[UTILS](#UTILS)</td></tr>
<tr><td>

0. [ft_isalpha](#ft_isalpha)
1. [ft_isdigit](#ft_isdigit)
1. [ft_isalnum](#ft_isalnum)
1. [ft_isascii](#ft_isascii)
1. [ft_isprint](#ft_isprint)
1. [ft_strlen](#ft_strlen)
1. [ft_memset](#ft_memset)
1. [ft_bzero](#ft_bzero)
1. [ft_memcpy](#ft_memcpy)
1. [ft_memmove](#ft_memmove)
1. [ft_strlcpy](#ft_strlcpy)
1. [ft_strlcat](#ft_strlcat)
1. [ft_toupper](#ft_toupper)
1. [ft_tolower](#ft_tolower)
1. [ft_strchr](#ft_strchr)
1. [ft_strrchr](#ft_strrchr)
1. [ft_strncmp](#ft_strncmp)
1. [ft_memchr](#ft_memchr)
1. [ft_memcmp](#ft_memcmp)
1. [ft_strnstr](#ft_strnstr)
1. [ft_atoi](#ft_atoi)
1. [ft_calloc](#ft_calloc)
1. [ft_strdup](#ft_strdup)
</td><td>

23. [ft_substr](#ft_substr)
1. [ft_strjoin](#ft_strjoin)
1. [ft_strtrim](#ft_strtrim)
1. [ft_split](#ft_split)
1. [ft_itoa](#ft_itoa)
1. [ft_strmapi](#ft_strmapi)
1. [ft_striteri](#ft_striteri)
1. [ft_putchar_fd](#ft_putchar_fd)
1. [ft_putstr_fd](#ft_putstr_fd)
1. [ft_putendl_fd](#ft_putendl_fd)
1. [ft_putnbr_fd](#ft_putnbr_fd)
</td><td>

34. [ft_lstnew](#ft_lstnew)
1. [ft_lstadd_front](#ft_lstadd_front)
1. [ft_lstsize](#ft_lstsize)
1. [ft_lstlast](#ft_lstlast)
1. [ft_lstadd_back](#ft_lstadd_back)
1. [ft_lstdelone](#ft_lstdelone)
1. [ft_lstclear](#ft_lstclear)
1. [ft_lstiter](#ft_lstiter)
1. [ft_lstmap](#ft_lstmap)
</td><td>

43. [ft_freeptr](#ft_freeptr)
1. [ft_isspace](#ft_isspace)
1. [ft_nbrlen](#ft_nbrlen)
1. [ft_isinset](#ft_isinset)
1. [ft_putnbr_base](#ft_putnbr_base)
1. [ft_printf](#ft_printf)
1. [get_next_line](#get_next_line)

</td></tr>
</tbody>
</table>

- [Referencias](#Referencias)
- [Glosario](#Glosario)

## LIBFT

### Ejecución

	cd libft
	make libft

### ft_isalpha
``` c
#include <ctype.h>
int isalpha(int c);

	La función ft_isalpha toma un carácter como entrada y determina si es un carácter alfabético o no. Un carácter alfabético se define como una letra del alfabeto inglés, ya sea mayúscula (A-Z) o minúscula (a-z). La función realiza una comparación para comprobar si el valor ASCII del carácter dado se encuentra dentro del rango de letras mayúsculas (65 a 90) o minúsculas (97 a 122). Si el carácter se encuentra dentro de alguno de estos rangos, devuelve un valor de 1024 (que puede ser cualquier valor distinto de cero), indicando que el carácter es un carácter alfabético. En caso contrario, devuelve 0, indicando que el carácter no es alfabético.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isdigit
``` c
#include <ctype.h>
int isdigit(int c);

	La función ft_isdigit toma un carácter como entrada y determina si es un dígito o no. Un dígito se define como un carácter numérico del 0 al 9. La función realiza una comparación para comprobar si el valor ASCII del carácter está dentro del rango de dígitos (48 a 57). Si el carácter está dentro de este rango, devuelve un valor distinto de cero, indicando que el carácter es un dígito. En caso contrario, devuelve 0, indicando que el carácter no es un dígito.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isalnum
``` c
#include <ctype.h>
int isalnum(int c);

	La función ft_isalnum toma un carácter como entrada y determina si es un carácter alfabético o un dígito. Un carácter alfabético se define como una letra del alfabeto inglés, ya sea mayúscula (A-Z) o minúscula (a-z). Un dígito se define como un carácter numérico del 0 al 9. La función realiza una serie de comparaciones para comprobar si el valor ASCII del carácter dado se encuentra dentro del rango de letras mayúsculas (65 a 90), letras minúsculas (97 a 122) o dígitos (48 a 57). Si el carácter está dentro de alguno de estos rangos, devuelve 8, indicando que se trata de un carácter alfabético o un dígito. En caso contrario, devuelve 0, indicando que el carácter no es ni un carácter alfabético ni un dígito.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isascii
``` c
#include <ctype.h>
int isascii(int c);

	La función ft_isascii toma un carácter como entrada y determina si está dentro del rango ASCII o no. El rango ASCII incluye caracteres con valores ASCII de 0 a 127. La función realiza una comparación para comprobar si el valor ASCII del carácter dado está dentro de este rango. Si el carácter está dentro del rango ASCII, devuelve 1, indicando que el carácter es válido. En caso contrario, devuelve 0, indicando que el carácter está fuera del rango ASCII.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isprint
``` c
#include <ctype.h>
int isprint(int c);

	La función ft_isprint toma un carácter como entrada y determina si es un carácter imprimible o no. Un carácter se considera imprimible si su valor ASCII es mayor que 31 (decimal) y menor que 127 (decimal). Los caracteres en este rango corresponden a caracteres imprimibles en la tabla ASCII, incluyendo alfabetos (A-Z, a-z), dígitos (0-9), signos de puntuación y símbolos especiales. La función realiza una simple comparación para comprobar si el valor ASCII del carácter dado se encuentra dentro del rango especificado. En caso afirmativo, devuelve un valor de 16384 (que puede ser cualquier valor distinto de cero), lo que indica que el carácter es imprimible. En caso contrario, devuelve 0, indicando que el carácter no es imprimible.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlen
``` c
#include <string.h>
size_t strlen(const char *s);

	La función ft_strlen toma como entrada un puntero a una cadena terminada en cero y calcula su longitud. Inicializa una variable 'i' a 0 y luego entra en un bucle que continúa hasta que encuentra un carácter terminador nulo ('\0'). En cada iteración, comprueba el valor en la posición de memoria apuntada por el puntero 'str' más el desplazamiento 'i'. Si el valor no es un terminador nulo, incrementa 'i' en 1. Este proceso continúa hasta que se encuentra el terminador nulo, indicando el final de la cadena. Finalmente, devuelve el valor de 'i', que representa la longitud de la cadena.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memset
``` c
#include <string.h>
void *memset(void str, int c, size_t n);

	La función ft_memset toma tres parámetros: str, c y n. Comienza asignando el valor de str a una variable str_ptr para mantener un registro del puntero original. Entra en un bucle que itera n veces, disminuyendo n en cada iteración. El propósito de este bucle es llenar cada byte del bloque de memoria con el valor c. Dentro del bucle, convierte el puntero str en un puntero unsigned char para asegurar una asignación correcta byte a byte. Asigna el valor de c al byte actual desreferenciando el puntero. A continuación, incrementa el puntero str para pasar al siguiente byte. Después de llenar todos los bytes, devuelve el str_ptr original, que ahora apunta al bloque de memoria después de haber sido llenado con el valor especificado. Esta función se utiliza comúnmente para inicializar la memoria o establecer regiones de memoria a un valor específico, como establecer una matriz de caracteres a terminadores nulos o establecer una matriz de enteros a ceros.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_bzero
``` c
#include <string.h>
void bzero(void str, size_t n);

	La función ft_bzero toma un puntero a un bloque de memoria y el número de bytes a poner a cero. Trata el bloque de memoria como una matriz de caracteres sin signo (bytes) e itera a través de cada byte del bloque. En cada iteración, asigna el valor 0 al byte actual desreferenciando el puntero 's' y convirtiéndolo en un puntero unsigned char. A continuación, incrementa el puntero 's' para que apunte al siguiente byte. Este proceso continúa hasta que 'n' se convierte en cero, momento en el que todo el bloque de memoria se ha puesto a cero. La función modifica la memoria directamente, poniendo a cero el número especificado de bytes a partir de la dirección de memoria dada.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memcpy
``` c
#include <string.h>
void *memcpy(void *dst, const void *src, size_t n);

	La función ft_memcpy toma un puntero al bloque de memoria destino (dest), un puntero al bloque de memoria origen (src) y el número de bytes a copiar (n). Comienza asignando el valor de 'dest' a 'dest_ptr' para no perder de vista el puntero de destino original. A continuación, comprueba si los punteros 'dest' y 'src' no son NULL. Si alguno de ellos es NULL, devuelve el puntero 'dest' ya que indica una operación inválida. En caso contrario, entra en un bucle que itera 'n' veces, copiando cada byte del origen al destino. La función convierte los punteros "dest" y "src" en punteros char para garantizar la copia en bytes. Dereferencia los punteros, asigna el valor en 'src' a 'dest', y luego incrementa los punteros 'dest' y 'src' para pasar al siguiente byte. Este proceso continúa hasta que 'n' se convierte en cero, indicando que se ha copiado el número necesario de bytes. Finalmente, devuelve el puntero 'dest_ptr', que apunta al inicio del bloque de memoria de destino.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memmove
``` c
#include <string.h>
void *memmove(void *dst, const void *src, size_t n);

	La función ft_memmove toma un puntero al bloque de memoria destino (dest), un puntero al bloque de memoria origen (src) y el número de bytes a copiar (n). Comienza asignando el valor de 'dest' a 'dest_ptr' para mantener un registro del puntero de destino original. A continuación, comprueba si los punteros 'dest' y 'src' no son NULL. Si alguno de ellos es NULL, devuelve el puntero 'dest' ya que indica una operación inválida. Comprueba si los punteros 'dest' y 'src' son iguales. Si son iguales, indica que las regiones de memoria se solapan, por lo que no es necesario realizar ninguna copia. En este caso, devuelve el puntero 'dest' sin modificar la memoria. Si el puntero de destino es mayor que el puntero de origen, significa que las regiones de memoria no se solapan, y puede realizar con seguridad una copia hacia adelante. Entra en un bucle que itera 'n' veces, copiando cada byte del origen al destino. La función utiliza aritmética de punteros y conversión de tipos para acceder a los bytes y copiarlos. Dereferencia los punteros 'dest' y 'src', asigna el valor en 'src' a 'dest', y luego incrementa ambos punteros 'dest' y 'src' para moverse al siguiente byte. Este proceso continúa hasta que 'n' se convierte en cero, indicando que se ha copiado el número necesario de bytes. Si el puntero de destino es menor que el puntero de origen, significa que las regiones de memoria se solapan, y necesita realizar una copia hacia atrás para evitar la corrupción de datos. Entra en un bucle que itera 'n' veces, empezando por

	Si ambos son iguales es que están solapados y no hay que hacer nada
si dst > src significa que las regiones no estan solapadas y se puede copiar
Si dst < src significa que estan solapadas y necesita revertir para evitar corrupción
SÍ puede solapar
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlcpy
``` c
#include <string.h>
size_t strlcpy(char *dst, const char *src, size_t size);

	La función ft_strlcpy toma un puntero a la cadena de destino (dest), un puntero a la cadena de origen (src) y el límite de tamaño del búfer de destino (n). Inicializa una variable 'i' a 0 para controlar la longitud de la cadena de origen. A continuación, entra en un bucle que itera hasta que llega al final de la cadena de origen, identificado por un carácter terminador nulo ('\0'). En cada iteración, incrementa 'i' en 1 para contar la longitud de la cadena fuente.

	Después de contar la longitud, comprueba si el límite de tamaño 'n' es cero. Si 'n' es cero, significa que no hay espacio en el búfer de destino, por lo que la función devuelve la longitud de la cadena de origen.

	En caso contrario, entra en otro bucle que copia caracteres de la cadena de origen al búfer de destino. Disminuye 'n' para tener en cuenta el espacio ocupado por el carácter terminador nulo. También comprueba si el carácter actual de la cadena de origen no es un terminador nulo ('\0') para continuar copiando. Dentro del bucle, asigna el valor en 'src' a 'dest' e incrementa los punteros 'dest' y 'src' para pasar al siguiente carácter. Este proceso continúa hasta que 'n' se convierte en cero o se alcanza el terminador nulo. Por último, añade un carácter terminador nulo al final del búfer de destino para asegurarse de que termina correctamente, y devuelve la longitud de la cadena de origen.

Nota: La función asume que el buffer de destino tiene espacio suficiente para alojar al menos 'n' caracteres más el terminador nulo. De lo contrario, puede provocar un desbordamiento del búfer.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlcat
``` c
#include <string.h>
size_t strlcat(char *dst, const char *src, size_t size);

Función no estandar
Más eficiente y seguro que strlcat

	La función ft_strlcat toma un puntero a la cadena de destino (dest), un puntero a la cadena de origen (src) y el límite de tamaño del búfer de destino (n). Comienza declarando las variables 'dest_len', 'total_len' y 's'. Comprueba si el puntero 'dest' o 'src' es NULL y el límite de tamaño 'n' es cero. Si ambas condiciones son ciertas, devuelve 0 para indicar que la operación no es válida. Asigna el puntero 'src' a 's' para mantener la pista del puntero fuente original. Inicializa 'dest_len' a 0 para contar la longitud de la cadena de destino. Entra en un bucle que itera hasta que alcanza el final de la cadena de destino o el límite de tamaño 'n'. En cada iteración, incrementa 'dest_len' en 1 y comprueba si el carácter actual de la cadena de destino no es un terminador nulo ('\0'). También comprueba si 'dest_len' es menor que 'n' para asegurarse de que se mantiene dentro del límite. Después de contar la longitud de la cadena de destino, comprueba si 'dest_len' es menor que 'n'. Si es cierto, significa que todavía hay espacio en el búfer de destino para añadir caracteres de la cadena de origen. Calcula el "total_len" sumando la longitud de la cadena de destino (dest_len) y la longitud de la cadena de origen (str_len(s)). Si 'dest_len' ya es igual o mayor que 'n', significa que el búfer de destino ya está lleno, por lo que devuelve directamente 'n' más la longitud de la cadena de origen (str_len(s)). Entra en otro bucle que copia n caracteres de la cadena de origen al búfer de destino. Comprueba si el carácter actual de la cadena de origen no es un terminador nulo ('\0') y si todavía hay espacio en el búfer de destino ('dest_len + 1 < n'). Dentro del bucle, asigna el valor en 's' a 'dest' e incrementa los punteros 'dest' y 's' para pasar al siguiente carácter. También incrementa 'dest_len' para controlar la longitud de la cadena concatenada. Este proceso continúa hasta el final de la cadena de origen o hasta que no queda espacio en el búfer de destino. Por último, añade un carácter terminador nulo al final del búfer de destino para asegurarse de que termina correctamente, y devuelve el valor 'total_len', que representa la longitud total de la cadena concatenada.

Nota: La función asume que el buffer de destino tiene espacio suficiente para alojar al menos 'n' caracteres más el terminador nulo. De lo contrario, puede provocar un desbordamiento del búfer.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_toupper
``` c
#include <ctype.h>
int toupper(int c);

	La función ft_toupper toma un carácter de entrada 'c'.

	Comprueba si 'c' está en el rango de letras minúsculas, que corresponde a los valores ASCII de 97 a 122. Si 'c' es una letra minúscula, resta 32 a su valor ASCII para convertirla en la letra mayúscula correspondiente. Si 'c' es una letra minúscula, resta 32 a su valor ASCII para convertirla en la letra mayúscula correspondiente. Esta conversión es posible porque los valores ASCII de las letras mayúsculas y minúsculas tienen una diferencia de 32. Por último, devuelve la letra mayúscula convertida si 'c' era una letra minúscula, o el propio carácter de entrada si 'c' no era una letra minúscula.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_tolower
``` c
#include <ctype.h>
int tolower(int c);

	La función ft_tolower toma un carácter de entrada 'c'.

	Comprueba si 'c' está en el rango de letras mayúsculas, que corresponde a los valores ASCII de 65 a 90. Si 'c' es una letra mayúscula, añade 32 a su valor ASCII para convertirla en la letra minúscula correspondiente. Si 'c' es una letra mayúscula, añade 32 a su valor ASCII para convertirla en la letra minúscula correspondiente. Esta conversión es posible porque los valores ASCII de las letras mayúsculas y minúsculas tienen una diferencia de 32. Por último, devuelve la letra minúscula convertida si 'c' era una letra mayúscula, o el propio carácter de entrada si 'c' no era una letra mayúscula.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strchr
``` c
#include <string.h>
char *strchr(const char *s, int c);

	La función ft_strchr toma un puntero a la cadena de entrada 'str' y un entero 'c' que representa un carácter. Entra en un bucle que itera hasta llegar al final de la cadena, identificado por un carácter terminador nulo ('\0'). En cada iteración, comprueba si el carácter actual de la cadena es igual al carácter 'c' buscado. Si se encuentra una coincidencia, devuelve un puntero a ese carácter de la cadena. Si no se encuentra ninguna coincidencia hasta el final de la cadena, comprueba si el último carácter es igual a 'c'. Esta comprobación es necesaria porque el bucle sale antes de comprobar el último carácter. Si el último carácter coincide con 'c', devuelve un puntero a ese carácter. Si no se encuentra ninguna coincidencia, significa que el carácter 'c' no está presente en la cadena, por lo que devuelve NULL.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strrchr
``` c
#include <string.h>
char *strrchr(const char *s, int c);

	La función ft_strrchr toma un puntero a la cadena de entrada 'str' y un entero 'c' que representa un carácter. Declara un puntero 'aux' y lo inicializa a NULL. Introduce un bucle que itera hasta llegar al final de la cadena, identificado por un carácter terminador nulo ('\0'). En cada iteración, comprueba si el carácter actual de la cadena es igual al carácter 'c' buscado. Si se encuentra una coincidencia, actualiza el puntero 'aux' para que apunte a ese carácter de la cadena. De esta forma, 'aux' mantiene la pista de la última aparición del carácter. Después del bucle, comprueba si el último carácter es igual a 'c'. Si el último carácter coincide con 'c', devuelve un puntero a ese carácter. Si el último carácter no es igual a 'c', significa que el carácter 'c' no está presente en la cadena, por lo que devuelve el puntero 'aux'. El puntero 'aux' sería NULL si no se encontrara ninguna ocurrencia de 'c' durante el bucle, indicando que 'c' no está presente en la cadena.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strncmp
``` c
#include <string.h>
int strncmp(const char *s1, const char *s2, size_t n);

	La función ft_strncmp toma tres parámetros: s1, s2 y n. Primero comprueba si n es cero. Si es cierto, significa que no debe compararse ningún carácter, por lo que devuelve 0 para indicar igualdad. La función entra en un bucle que itera hasta que llega al final de s1 o s2, o hasta que n se convierte en 1. En cada iteración, compara los caracteres de s1 con los de s2. En cada iteración, compara los caracteres en las posiciones actuales de s1 y s2. Si los caracteres son iguales y n es mayor que 1, significa que se ha encontrado una coincidencia potencial, por lo que incrementa s1, s2 y disminuye n para pasar al siguiente carácter. La función continúa comparando caracteres hasta que se encuentra una diferencia o n se convierte en 1. Una vez que el bucle termina, significa que se ha alcanzado el final de s1 o s2, o bien que n se convierte en 1. Si las cadenas son iguales, devuelve 0. Si s1 es menor que s2, significa que s1 es lexicográficamente menor, por lo que devuelve un valor negativo. Si s1 es mayor que s2, significa que s1 es lexicográficamente mayor, por lo que devuelve un valor positivo. Al convertir los caracteres en unsigned char, la función garantiza una comparación correcta de los caracteres sin problemas de extensión de signos. Esta función puede utilizarse para comparar cadenas en orden lexicográfico hasta una longitud especificada.

Devuelve:
*. 0    si s1 = s2
*. > 0  si s1 > s2
* < 0   si s2 > s1
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memchr
``` c
#include <string.h>
void *memchr(const void *s, int c, size_t n);

	La función ft_memchr toma un puntero al bloque de memoria 'str', un entero 'c' que representa un carácter, y un size_t 'n' que especifica el número de bytes a buscar dentro del bloque de memoria. Introduce un bucle que itera 'n' veces, decrementando 'n' en cada iteración. En cada iteración, comprueba si el byte actual del bloque de memoria, al que se accede convirtiendo 'str' en un puntero unsigned char, es igual al carácter 'c' que se está buscando. Si se encuentra una coincidencia, devuelve un puntero a ese byte en el bloque de memoria. Si no se encuentra ninguna coincidencia hasta el final del bucle, significa que el carácter 'c' no está presente en el bloque de memoria, por lo que devuelve NULL.

	A diferencia de strchr, memchr no se detiene aunque encuentre el final de cadena "\0"
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memcmp
``` c
#include <string.h>
int memcmp(const void *s1, const void *s2, size_t n);

	La función ft_memcmp toma dos punteros, s1 y s2, que apuntan a las áreas de memoria a comparar, y el número de bytes a comparar, n. Introduce un bucle que itera n veces, decrementando n en cada iteración. El propósito de este bucle es comparar cada byte en las áreas de memoria hasta que n se convierte en cero. Dentro del bucle, comprueba si el valor en el byte actual de s1 es diferente del valor en el byte actual de s2. Si se encuentra una diferencia, devuelve la diferencia entre los dos bytes. Como el tipo de retorno es int, la diferencia se calcula restando el valor del byte actual de s2 del valor del byte actual de s1. Al convertir los punteros a unsigned char, la función asegura que la comparación se realiza byte a byte sin problemas de extensión de signo. Después de comparar cada byte, si no se encuentran diferencias, significa que las áreas de memoria son iguales, por lo que devuelve 0. Esta función se puede utilizar para comparar matrices, cadenas o cualquier otra área de memoria de forma genérica.
	Comparar aunque se encuentre con '\0'
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strnstr
``` c
#include <string.h>
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

	La función ft_strnstr toma tres parámetros: pajar, aguja y n. Comienza comprobando si pajar es NULL y n es cero. Si ambas condiciones son ciertas, devuelve NULL para indicar que la operación no es válida. A continuación, comprueba si needle es una cadena vacía ('\0'). Si es cierto, significa que siempre se considera que hay una cadena vacía al principio del pajar, por lo que devuelve un puntero al pajar. La función entra en un bucle que itera hasta que llega al final de la cadena del pajar o hasta que n se hace cero. En cada iteración, inicializa una variable j a 0 para llevar la cuenta de la posición actual en la cadena de agujas. A continuación, compara los caracteres en las posiciones actuales del pajar y la aguja. Si los caracteres son iguales y el carácter en la aguja no es un terminador nulo, significa que se ha encontrado una coincidencia potencial, por lo que incrementa j y comprueba si j es menor o igual que n para asegurarse de que se mantiene dentro del límite de búsqueda. También comprueba si el siguiente carácter de la aguja es un terminador nulo. Si es cierto, significa que se ha encontrado toda la aguja en el pajar, por lo que devuelve un puntero a la posición actual en el pajar. Si no se encuentra ninguna coincidencia, incrementa el pajar para pasar al siguiente carácter y continúa buscando. Una vez finalizado el bucle, significa que se ha alcanzado el final del pajar o que n es cero. En cualquier caso, significa que no se ha encontrado la subcadena, por lo que devuelve NULL para indicar la ausencia de la subcadena.

Nota: La función busca una subcadena dentro de los primeros 'n' caracteres de la cadena del pajar. Si 'n' es mayor que la longitud del pajar, buscará en toda la cadena del pajar.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_atoi
``` c
#include <stdlib.h>
int atoi(const char *nptr);

	La función ft_atoi escanea la cadena de entrada y la convierte en un número entero. Se salta cualquier carácter de espacio en blanco avanzando el puntero. Si se encuentra un signo más (+) o menos (-), determina el signo del número y avanza el puntero. A continuación, procesa cada dígito y calcula el valor entero correspondiente. Realiza comprobaciones para evitar el desbordamiento comparando el valor actual con el valor anterior multiplicado por el signo. Si se produce un desbordamiento, devuelve 0 si el signo es positivo o -1 si es negativo. Por último, devuelve el valor entero resultante.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_calloc
``` c
#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);

	La función ft_calloc toma dos parámetros: count y n. Primero realiza una comprobación para asegurar que el producto de count y n no desborda el tipo size_t. Si la comprobación falla, devuelve NULL para indicar un error. A continuación, llama a la función malloc para asignar memoria para count * n bytes. Si la asignación de memoria falla, malloc devuelve NULL, y ft_calloc también devuelve NULL para indicar un error. Si la asignación de memoria tiene éxito, realiza comprobaciones adicionales para manejar el caso en que n sea cero. Si n es cero, significa que el tamaño de cada elemento es cero, por lo que ft_calloc devuelve directamente la memoria asignada sin inicializarla. En caso contrario, llama a la función s_zero para inicializar el bloque de memoria asignado a todos los ceros. La función s_zero se define como una función estática en el código y pone a cero cada byte del bloque de memoria. Por último, ft_calloc devuelve el puntero al bloque de memoria asignado e inicializado. Esta función es útil cuando se necesita asignar memoria para una matriz e inicializarla a un valor específico, como cuando se pone a cero un buffer o se asigna memoria para una matriz de estructuras.

	La memoría asignada se establece a "\0". Limpia a diferencia de malloc
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strdup
``` c
#include <string.h>
char *strdup(const char *s);

	La función ft_strdup toma un único parámetro: src, que es un puntero a la cadena de origen. Comienza llamando a la función str_new para asignar memoria a la cadena duplicada. La función str_new es responsable de la asignación de memoria y se define como una función estática. Si la asignación de memoria falla, str_new devuelve NULL, y ft_strdup devuelve NULL también para indicar un error. Si la asignación de memoria tiene éxito, ft_strdup asigna el puntero devuelto a la variable dest. A continuación, ft_strdup entra en un bucle que itera hasta llegar al final de la cadena fuente comprobando si el carácter actual no es un terminador nulo. En cada iteración, asigna el valor del carácter actual en src a la posición de memoria apuntada por dest e incrementa ambos punteros para pasar al siguiente carácter. Después de copiar todos los caracteres, añade un terminador nulo al final de la cadena duplicada para garantizar una terminación correcta. Finalmente, ft_strdup devuelve el puntero de inicio, que apunta al principio de la cadena duplicada. La función es útil cuando se necesita crear una copia independiente de una cadena, permitiendo modificaciones en la cadena duplicada sin afectar a la original.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## ADICIONAL

### ft_substr
``` c
char	*ft_substr(char const *s, unsigned int start, size_t len);

	La función ft_substr toma tres parámetros: s, start y len. Primero comprueba que s no sea NULL. Si s es NULL, devuelve NULL para indicar un error. A continuación, comprueba si el índice de inicio es mayor que la longitud de la cadena de origen. Si es cierto, significa que el índice de inicio está más allá del final de la cadena de origen, por lo que pone len a 0 para crear una subcadena vacía. En caso contrario, comprueba si la longitud especificada supera los caracteres restantes de la cadena de origen después del índice de inicio. Si es cierto, ajusta len para que sea igual al número de caracteres que quedan en la cadena de origen después del índice de inicio. El siguiente paso es llamar a la función str_new para asignar memoria a la subcadena. La función str_new está definida como estática en el código y es la responsable de asignar la memoria. Si la asignación de memoria falla, str_new devuelve NULL, y ft_substr también devuelve NULL para indicar un error. Si la asignación de memoria tiene éxito o si len es cero, ft_substr asigna el puntero devuelto a la variable str e incrementa el puntero s por el índice de inicio para posicionarlo al principio de la subcadena deseada. También asigna el puntero str a la variable str_ptr para mantener un registro del inicio de la subcadena. A continuación, añade un terminador nulo al final de la subcadena para garantizar una terminación correcta. Por último, ft_substr entra en un bucle que copia caracteres de la cadena de origen a la subcadena. Comprueba si len no es cero y si el carácter actual en s no es un terminador nulo. Dentro del bucle, asigna el valor del carácter actual en s a la posición de memoria apuntada por str e incrementa ambos punteros para pasar al siguiente carácter. También decrementa len para llevar la cuenta de los caracteres que quedan por copiar. Este proceso continúa hasta que len se convierte en cero o hasta que se encuentra un terminador nulo. Una vez finalizado el bucle, ft_substr devuelve el puntero str_ptr, que apunta al principio de la subcadena asignada. La función es útil cuando se necesita extraer una porción de una cadena para crear una nueva cadena.
```

### ft_strjoin
``` c
char	*ft_strjoin(char const *s1, char const *s2);

	La función ft_strjoin toma dos parámetros: s1 y s2. Primero comprueba si s1 o s2 son NULL. Si es cierto, significa que falta una de las cadenas, y la función devuelve NULL para indicar un error. A continuación, llama a la función str_new para asignar memoria a la cadena concatenada. La función str_new está definida como estática en el código y es la responsable de asignar la memoria. Si la asignación de memoria falla, str_new devuelve NULL, y ft_strjoin también devuelve NULL para indicar un error. Si la asignación de memoria se realiza correctamente, ft_strjoin asigna el puntero devuelto a la variable str e incrementa la variable str_ptr para seguir el comienzo de la cadena concatenada. A continuación, entra en un bucle que copia los caracteres de s1 en la nueva cadena hasta que se encuentra un terminador nulo en s1. Dentro del bucle, asigna el valor del carácter actual en s1 a la posición de memoria apuntada por str e incrementa ambos punteros para pasar al siguiente carácter. El bucle continúa hasta el final de s1. Después de copiar s1, ft_strjoin entra en otro bucle para copiar caracteres de s2 a la nueva cadena. Realiza el mismo proceso de copia de caracteres que en el bucle anterior. Una vez alcanzado el final de s2, añade un terminador nulo al final de la cadena concatenada para garantizar una terminación correcta. Finalmente, ft_strjoin devuelve el puntero str_ptr, que apunta al principio de la cadena concatenada. La función es útil cuando se necesita combinar dos cadenas en una nueva cadena.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strtrim
``` c
char	*ft_strtrim(char const *s1, char const *set);

	La función ft_strtrim toma dos parámetros: s1 y set. Primero comprueba si s1 o set son NULL. Si es cierto, significa que falta una de las cadenas, y la función devuelve NULL para indicar un error. A continuación, inicializa la variable start a 0 y entra en un bucle para encontrar el índice del primer carácter no coincidente en s1 iterando sobre él. Dentro del bucle, utiliza la función char_check para determinar si el carácter actual de s1 coincide con algún carácter del conjunto. Si hay coincidencia, incrementa la variable start para pasar al siguiente carácter. Una vez finalizado el bucle, la variable start representa el índice del primer carácter no coincidente o el final de la cadena si todos los caracteres coinciden con el conjunto. Del mismo modo, inicializa la variable end a la longitud de s1 y entra en un bucle para encontrar el índice del último carácter no coincidente en s1 iterando sobre él en sentido inverso. Dentro del bucle, utiliza la función char_check para determinar si el carácter actual de s1 coincide con algún carácter del conjunto. Si coincide, decrementa la variable end para pasar al carácter anterior. Una vez finalizado el bucle, la variable end representa el índice del último carácter no coincidente más uno. A continuación, la función ft_strtrim llama a la función str_new para asignar memoria a la cadena recortada. La función str_new está definida como estática en el código y es la responsable de asignar la memoria. Si la asignación de memoria falla, str_new devuelve NULL, y ft_strtrim también devuelve NULL para indicar un error. Si la asignación de memoria se realiza correctamente, ft_strtrim copia los caracteres no coincidentes de s1 a la cadena de recorte comenzando por el índice inicial y terminando en el índice final. Añade un terminador nulo al final de la cadena recortada para garantizar una terminación correcta. Por último, devuelve el puntero de recorte, que apunta al principio de la cadena recortada. La función es útil cuando se necesita eliminar los caracteres iniciales y finales de una cadena basándose en un conjunto dado.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_split
``` c
char	**ft_split(char const *s, char c);

	La función ft_split toma un puntero a la cadena de entrada 's' y un carácter 'c' que actúa como delimitador. Calcula el número de subcadenas presentes en la cadena llamando a la función count_words. A continuación, asigna memoria a una matriz de punteros de cadena para almacenar las subcadenas, incluido un puntero NULL adicional al final.

	La función split se encarga de rellenar la matriz con las subcadenas. Inicializa dos índices 'i' y 'j' para llevar la cuenta de las posiciones en la cadena. Recorre la cadena mientras 'i' es menor que el número de palabras. Omite los caracteres delimitadores y extrae una subcadena utilizando la función ft_substr. Si la asignación de memoria para la subcadena falla, la memoria previamente asignada se libera utilizando la función free_array, y la función devuelve NULL. Una vez extraídas todas las subcadenas y almacenadas en la matriz, se coloca un puntero NULL al final de la matriz para indicar el final de las subcadenas.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_itoa
``` c
char	*ft_itoa(int n);

	La función ft_itoa convierte el número entero dado en una representación de cadena. Primero determina el signo del número comprobando si es negativo. Calcula la longitud de la cadena resultante contando el número de dígitos del valor absoluto del número entero. Se asigna memoria para almacenar la cadena resultante, incluyendo espacio para el signo y el terminador nulo. La conversión se realiza extrayendo iterativamente los dígitos del número entero mediante operaciones de módulo y división. A continuación, los dígitos se convierten en caracteres añadiendo el valor ASCII "0". Los dígitos se añaden a la cadena en orden inverso para garantizar la representación correcta del número. Por último, se añade el signo si es necesario, se añade el terminador nulo y se devuelve la cadena resultante.

Nota: La persona que llama es responsable de liberar la memoria asignada dinámicamente a la cadena devuelta cuando ya no la necesite.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strmapi
``` c
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

	La función ft_strmapi crea una nueva cadena aplicando la función especificada a cada carácter de la cadena de entrada. En primer lugar, determina la longitud de la cadena de entrada mediante la función auxiliar str_len. La memoria se asigna para almacenar la cadena resultante, incluido el espacio para el valor nulo. Si se produce un error en la asignación de memoria, se devuelve NULL. A continuación, la función recorre en iteración cada carácter de la cadena de entrada, pasando el índice y el carácter actuales a la función proporcionada. La función devuelve un nuevo carácter basado en el índice y el carácter de entrada, que se almacena en la cadena resultante. Por último, se anexa el terminador nulo y se devuelve la cadena resultante. Nota: El autor de la llamada es responsable de liberar la memoria asignada dinámicamente para la cadena devuelta cuando ya no sea necesaria.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_striteri
``` c
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

	La función ft_striteri recorre en iteración cada carácter de la cadena de entrada, pasando el índice actual y un puntero al carácter de la función proporcionada. Si la cadena de entrada y los punteros de función no son NULL, comienza la iteración. Dentro del bucle, la función se aplica a cada carácter, lo que permite que la función realice alguna operación o modificación en el carácter. El índice se incrementa con cada iteración y el puntero al carácter se incrementa para pasar al siguiente carácter de la cadena. La iteración continúa hasta que se alcanza el terminador nulo de la cadena. Si la cadena de entrada o el puntero de función es NULL, la función no hace nada. Nota: La función opera directamente en la cadena de entrada y la modifica en su lugar. No hay valor de retorno.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putchar_fd
``` c
void	ft_putchar_fd(char c, int fd);

	La función ft_putchar_fd escribe un solo carácter en el descriptor de archivo especificado. Utiliza la llamada al sistema de escritura para escribir el carácter en el descriptor de archivo. La función supone que la operación de escritura se realizará correctamente y no incluye el control explícito de errores. Nota: Es importante asegurarse de que el descriptor de archivo sea válido y esté abierto para escritura antes de llamar a esta función para evitar comportamientos o errores inesperados.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putstr_fd
``` c
void	ft_putstr_fd(char *s, int fd);

	La función ft_putstr_fd escribe el contenido de una cadena en el descriptor de archivo especificado. Utiliza la llamada al sistema de escritura para escribir la cadena en el descriptor de archivo. La función supone que la operación de escritura se realizará correctamente y no incluye el control explícito de errores. Nota: Es importante asegurarse de que el descriptor de archivo sea válido y esté abierto para escritura antes de llamar a esta función para evitar comportamientos o errores inesperados.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putendl_fd
``` c
void	ft_putendl_fd(char *s, int fd);

	La función ft_putendl_fd escribe el contenido de una cadena en el descriptor de archivo especificado, seguido de un carácter de nueva línea ('\n'). Utiliza la llamada al sistema de escritura para escribir la cadena y el carácter de nueva línea en el descriptor de archivo. La función supone que la operación de escritura se realizará correctamente y no incluye el control explícito de errores. Nota: Es importante asegurarse de que el descriptor de archivo sea válido y esté abierto para escritura antes de llamar a esta función para evitar comportamientos o errores inesperados.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putnbr_fd
``` c
void	ft_putnbr_fd(int n, int fd);

	La función ft_putnbr_fd escribe un entero en el descriptor de archivo especificado. Utiliza la llamada al sistema de escritura para generar el entero como caracteres en el descriptor de archivo. Si el entero es igual al valor mínimo representable de un long long int (LLONG_MIN), la función escribe directamente la cadena "-9223372036854775808" en el descriptor de archivo. De lo contrario, la función convierte el entero en su representación de cadena en la base dada (decimal de forma predeterminada) y genera los caracteres resultantes. Nota: La función asume que la operación de escritura se realizará correctamente y no incluye el control explícito de errores.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>


## BONUS

### ft_lstnew
``` c
t_list	*ft_lstnew(void *content);

	La función ft_lstnew toma un puntero al contenido que debe almacenarse en el nuevo elemento de lista. Comienza asignando memoria para el nuevo elemento de la lista usando la función 'malloc', con el tamaño de la estructura 't_list'. Si se produce un error en la asignación de memoria (es decir, 'malloc' devuelve NULL), la función devuelve NULL, lo que indica que no pudo crear el nuevo elemento de la lista debido a la escasez de memoria.

	Si la asignación de memoria se realiza correctamente, la función procede a establecer los campos 'content' y 'next' del nuevo elemento de lista. Al campo 'content' se le asigna el valor del puntero 'content' pasado como argumento, lo que permite que el elemento list almacene el contenido proporcionado por el usuario. El campo 'next' se inicializa en NULL, lo que indica que este elemento de la lista no apunta a ningún otro elemento (es el último elemento de la lista inicialmente). Después de configurar el contenido y los campos siguientes, la función devuelve un puntero al elemento de lista recién creado, lo que permite al usuario usarlo según sea necesario para crear una lista vinculada.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstadd_front
``` c
void	ft_lstadd_front(t_list **lst, t_list *new);

	La función ft_lstadd_front toma un puntero al puntero al primer elemento de una lista enlazada (lst) y un puntero al elemento que se va a agregar (new). Comienza comprobando si 'lst' o 'new' es NULL. Si alguno de ellos es NULL, indica una operación no válida y la función se devuelve sin realizar ningún cambio. Asigna el puntero 'siguiente' del elemento 'nuevo' al puntero del primer elemento (*lst), haciendo que el elemento 'nuevo' apunte al primer elemento actual de la lista. A continuación, actualiza el puntero al primer elemento (*lst) para que apunte al elemento 'new', convirtiéndolo en el nuevo primer elemento de la lista. Este paso garantiza que el elemento 'new' se agregue al principio de la lista. Finalmente, la función regresa y la lista ahora contiene el nuevo elemento en la parte delantera.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstsize
``` c
int		ft_lstsize(t_list *lst);

	La función ft_lstsize toma un puntero al primer elemento de una lista vinculada (lst). Comienza inicializando una variable 'i' a 0. Esta variable se utilizará para realizar un seguimiento del número de elementos de la lista. A continuación, la función entra en un bucle while que recorre en iteración la lista enlazada. Durante cada iteración, comprueba si el puntero 'lst' no es NULL. Si 'lst' no es NULL, significa que hay al menos un elemento más en la lista, por lo que la función avanza al siguiente elemento actualizando 'lst' a lst->next. Al mismo tiempo, incrementa la variable 'i' en 1, lo que indica que se ha contado un elemento más. El bucle continúa hasta que el puntero 'lst' se convierte en NULL, lo que significa que se ha alcanzado el final de la lista. En este punto, la función ha contado el número total de elementos de la lista y devuelve el valor de 'i', que representa el tamaño de la lista enlazada.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstlast
``` c
t_list	*ft_lstlast(t_list *lst);

	La función ft_lstlast toma un puntero al primer elemento de una lista vinculada (lst). Comienza comprobando si el puntero 'lst' es NULL, lo que indica una lista vacía. Si 'lst' es NULL, significa que no hay elementos en la lista, por lo que la función devuelve NULL para indicar una lista vacía. Si la lista no está vacía, la función procede a buscar el último elemento de la lista mediante un bucle while. Durante cada iteración, comprueba si el puntero 'next' del elemento actual (lst->next) no es NULL. Si el puntero 'next' no es NULL, significa que hay más elementos en la lista, por lo que la función avanza al siguiente elemento estableciendo 'lst' en lst->next. Este proceso continúa hasta que se alcanza el último elemento, que es el elemento cuyo puntero "siguiente" es NULL. Una vez que se encuentra el último elemento, la función devuelve un puntero a ese elemento, apuntando efectivamente al último elemento de la lista.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstadd_back
``` c
void	ft_lstadd_back(t_list **lst, t_list *new);

	La función ft_lstadd_back toma un puntero al puntero al primer elemento de una lista vinculada (lst) y un puntero al elemento que se va a agregar (new). Comienza comprobando si 'lst' o 'new' es NULL. Si alguno de ellos es NULL, indica una operación no válida y la función se devuelve sin realizar ningún cambio. Comprueba si el puntero al primer elemento de la lista (*lst) es NULL. Si es NULL, significa que la lista está vacía. En este caso, asigna el elemento 'new' al puntero al primer elemento (*lst) y devuelve. Este paso es necesario para manejar el caso en el que la lista está inicialmente vacía. Si la lista no está vacía, inicializa un puntero temporal 'temp' y le asigna el valor del puntero al primer elemento (*lst). A continuación, recorre la lista mediante un bucle hasta llegar al último elemento, que se indica con un NULL puntero 'siguiente'. Dentro del bucle, actualiza el puntero 'temp' para que apunte al siguiente elemento de cada iteración. Una vez que el bucle llega al último elemento, asigna el elemento 'nuevo' al puntero 'siguiente' del último elemento, agregándolo efectivamente al final de la lista. Finalmente, la función regresa y la lista ahora contiene el nuevo elemento al final.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstdelone
``` c
void	ft_lstdelone(t_list *lst, void (*del)(void *));

	La función ft_lstdelone toma un puntero a un elemento de una lista enlazada (lst) y un puntero de función 'del' que apunta a una función responsable de liberar la memoria del contenido de ese elemento de lista. Comienza comprobando si el puntero 'lst' o el puntero de la función 'del' es NULL. Si alguno de ellos es NULL, indica una operación no válida o un intento de eliminar un elemento no existente, y la función regresa sin hacer nada. A continuación, la función procede a eliminar el elemento siguiendo los siguientes pasos:
	Llama a la función 'del' para liberar la memoria del contenido (si se asignó dinámicamente). Este paso garantiza que la memoria ocupada por el contenido del elemento se libere correctamente. Después de liberar el contenido, el elemento en sí se desasigna utilizando la función free para liberar la memoria ocupada por el elemento. Por último, el puntero 'lst' (pasado como parámetro) se establece en NULL. Sin embargo, es importante tener en cuenta que esta acción no afecta al puntero original fuera de esta función, ya que es una copia del puntero original pasado a la función. El resultado es que la memoria ocupada por el elemento especificado y su contenido (si existe) se desasigna, y el puntero al elemento sigue siendo válido, pero se establece en NULL dentro del ámbito de la función.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstclear
``` c
void	ft_lstclear(t_list **lst, void (*del)(void *));

	La función ft_lstclear toma un puntero al puntero al primer elemento de una lista enlazada (lst) y un puntero de función 'del' que apunta a una función responsable de liberar la memoria del contenido de cada elemento de la lista. Comienza comprobando si el puntero 'lst', el puntero de la función 'del' o el puntero al primer elemento (*lst) es NULL. Si alguno de ellos es NULL, indica una operación no válida o una lista vacía, y la función regresa sin hacer nada. A continuación, la función procede a borrar la lista de forma recursiva mediante los siguientes pasos:
	Llama a ft_lstclear de forma recursiva en el puntero "siguiente" del elemento actual, recorriendo efectivamente la lista hasta su final. Para cada elemento durante el recorrido recursivo, se llama a la función 'del' para liberar la memoria del contenido (si se asignó dinámicamente). Este paso garantiza que la memoria ocupada por el contenido de cada elemento se libere correctamente. Después de liberar el contenido, el elemento actual se desasigna utilizando la función free para liberar la memoria ocupada por el propio elemento. Por último, el puntero 'lst' se establece en NULL para indicar que la lista está vacía. El resultado es que se liberan todos los elementos de la lista vinculada, incluido su contenido, y el puntero 'lst' se establece en NULL, lo que indica que la lista está vacía.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstiter
``` c
void	ft_lstiter(t_list *lst, void (*f)(void *));

	La función ft_lstiter toma un puntero al primer elemento de una lista enlazada (lst) y un puntero de función 'f' que apunta a una función que se aplicará al contenido de cada elemento de la lista. Comienza comprobando si el puntero 'lst' o el puntero de la función 'f' es NULL. Si alguno de ellos es NULL, indica una operación no válida o un intento de iterar sobre una lista vacía, y la función se devuelve sin hacer nada. A continuación, la función procede a iterar sobre cada elemento de la lista enlazada mediante un bucle while. Durante cada iteración, hace lo siguiente:
	Aplica la función 'f' al contenido del elemento actual (lst->content). Este paso permite que 'f' procese o modifique el contenido según sea necesario. Avanza el puntero 'lst' para que apunte al siguiente elemento de la lista estableciéndolo en lst->next. Esto permite que la función se mueva al siguiente elemento en la siguiente iteración del bucle. El bucle continúa hasta que el puntero 'lst' se convierte en NULL, lo que indica el final de la lista. En otras palabras, la función itera sobre todos los elementos de la lista enlazada, aplicando la función 'f' al contenido de cada elemento en el proceso. El resultado es que la memoria ocupada por el elemento especificado y su contenido (si existe) se desasigna, y el puntero al elemento sigue siendo válido, pero se establece en NULL dentro del ámbito de la función.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstmap
``` c
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

	La función ft_lstmap toma un puntero al primer elemento de una lista enlazada existente (lst), un puntero de función 'f' que apunta a una función responsable de transformar el contenido de cada elemento de la lista, y un puntero de función 'del' que apunta a una función utilizada para liberar la memoria del contenido de cada elemento en caso de errores. La función comprueba primero si el puntero 'lst' o cualquiera de los punteros de función 'f' y 'del' es NULL. Si alguno de ellos es NULL, indica una operación no válida o un intento de asignar una lista vacía, y la función devuelve NULL sin hacer nada. A continuación, la función procede a crear una nueva lista aplicando la función 'f' al contenido de cada elemento de la lista original. Lo hace mediante un bucle while que recorre en iteración la lista original. Durante cada iteración, se realizan los siguientes pasos:
	La función 'f' se aplica al contenido del elemento actual (lst->content) para transformarlo. A continuación, el contenido transformado se utiliza para crear un nuevo elemento mediante la función lst_new. Si se produce un error en la asignación de memoria, la función libera la memoria de los elementos recién creados en la nueva lista mediante la función lst_clear y devuelve NULL para indicar un error. Si la asignación de memoria se realiza correctamente, el nuevo elemento se agrega a la nueva lista actualizando el puntero 'siguiente' del último elemento (new_set) para que apunte al elemento recién creado. El puntero 'new_set' se mueve para apuntar al elemento recién agregado para realizar un seguimiento del último elemento de la nueva lista. A continuación, el puntero 'lst' se mueve al siguiente elemento de la lista original para la siguiente iteración. Después de procesar todos los elementos de la lista original, la función devuelve un puntero al primer elemento de la nueva lista, apuntando efectivamente a la nueva lista que contiene los elementos transformados. Si se produce algún error durante el proceso, la función devuelve NULL después de liberar la memoria de la lista recién creada y el contenido de sus elementos mediante la función lst_clear. Es importante tener en cuenta que la función lst_new se usa para crear un nuevo elemento de lista con el contenido transformado y que la función lst_clear se usa para desasignar memoria en caso de errores.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## UTILS

> Funciones útiles añadidas una vez se ha presentado el proyecto. Cuidado ya que estás no se piden.

### ft_freeptr
``` c
void	ft_freeptr(char **ptr);

Libera la memoria apuntada por un puntero y lo pone a nulo. Útil para ahorrar algunas líneas y cumplir la norma.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isspace
``` c
int		ft_isspace(char c);

Devuelve si el caracter c es un espacio, tabulación, salto de línea, etc.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_nbrlen
``` c
int		ft_nbrlen(long int n);

Devulve el número de cifras de un número.

```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isinset
``` c
int		ft_isinset(char c, char const *set);

Devulve 1 si el caracter c está incluido en la cadena set o 0 si al contrario.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>


### ft_putnbr_base
``` c
int		ft_putnbr_base(char c, unsigned long nbr, char *base);

Char c es el tipo de número a imprimir. p (puntero),
Imprime por pantalla cualquier número sin signo dada una base. Ex: binario `01`, hexadecimal `0123456789ABCDEF`
Para imprimir con signo, ver [ft_putnbr_fd](#ft_putnbr_fd)
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_printf
``` c
int		ft_printf(char const *s, ...);

Imprime por pantalla.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### get_next_line
``` c
char	*get_next_line(int fd);		// BONUS MODE

Lee un archivo o varios y muestra línea a línea.
Usar:

```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## Referencias
### Librerías explicadas en español
- https://tutoriales.edu.lat/pub/c-standard-library/ctype-h/biblioteca-c-ctype-h
- https://tutoriales.edu.lat/pub/c-standard-library/string-h/biblioteca-c-string-h
- https://tutoriales.edu.lat/pub/c-standard-library/stdlib-h/biblioteca-c-stdlib-h

### Diferencia memcpy y memmove
https://clang.19633.com/es/c1-3/1003050520.html

### Diferencia memchr y strchr
https://stackoverflow.com/questions/4260109/differences-between-memchr-and-strchr

### Compilación
https://juncotic.com/compilacion-fuente-ejecutable/

### ASCII table
https://cdn.sparkfun.com/assets/home_page_posts/2/1/2/1/ascii_table_black.png

### LIBFT 42 explicado en ingles
- https://42.nauman.cc/2023/05/31/libft-introduction/
- https://github.com/vvarodi/libft_42?tab=readme-ov-file

### Posibles consejos globales
- https://haglobah.github.io/Mastering-42/holy_graph/libft.html
- https://ricardovelac.github.io/42docs/proyectos/libft.html
- https://42-cursus.gitbook.io/guide/rank-00/libft

## All Mans
- [man isalpha](https://man7.org/linux/man-pages/man3/isalpha.3.html)
- [man isdigit](https://man7.org/linux/man-pages/man3/isdigit.3.html)
- [man isalnum](https://man7.org/linux/man-pages/man3/isalnum.3.html)
- [man isascii](https://man7.org/linux/man-pages/man3/isascii.3.html)
- [man isprint](https://man7.org/linux/man-pages/man3/isprint.3.html)
- [man strlen](https://man7.org/linux/man-pages/man3/strlen.3.html)
- [man memset](https://man7.org/linux/man-pages/man3/memset.3.html)
- [man bzero](https://man7.org/linux/man-pages/man3/bzero.3.html)
- [man memcpy](https://man7.org/linux/man-pages/man3/memcpy.3.html)
- [man memmove](https://man7.org/linux/man-pages/man3/memmove.3.html)
- [man strlcpy](https://man7.org/linux/man-pages/man3/strlcpy.3.html)
- [man strlcat](https://man7.org/linux/man-pages/man3/strlcat.3.html)
- [man toupper](https://man7.org/linux/man-pages/man3/toupper.3.html)
- [man tolower](https://man7.org/linux/man-pages/man3/tolower.3.html)
- [man strchr](https://man7.org/linux/man-pages/man3/strchr.3.html)
- [man strrchr](https://man7.org/linux/man-pages/man3/strrchr.3.html)
- [man strncmp](https://man7.org/linux/man-pages/man3/strncmp.3.html)
- [man memchr](https://man7.org/linux/man-pages/man3/memchr.3.html)
- [man memcmp](https://man7.org/linux/man-pages/man3/memcmp.3.html)
- [man strnstr](https://man7.org/linux/man-pages/man3/strnstr.3.html)
- [man atoi](https://man7.org/linux/man-pages/man3/atoi.3.html)
- [man calloc](https://man7.org/linux/man-pages/man3/calloc.3.html)

## Glosario

- relink: La mayoría de las veces, en el contexto de un Makefile, "relink" podría referirse a volver a generar un ejecutable o una biblioteca compartida después de que se hayan realizado cambios en el código fuente o en otros archivos relevantes. Esto generalmente implica volver a compilar todos los archivos fuente y luego volver a enlazarlos para crear el ejecutable o la biblioteca.

- null: NULL se define típicamente como un entero constante de valor cero.

- size_t: size_t es un tipo de datos utilizado en C y C++ para representar el tamaño de objetos en bytes.

[ $${\color{red}VOLVER}$$ ](../../README.md)
