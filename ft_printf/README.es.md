![Rating](/assets/images/header.png)

# FT_PRINTF

<table align="center">
<caption>Tabla de contenidos</caption>
<tbody>
<tr><td align="center"><b>

[FT_PRINTF](#ft_printf)</b></td>
    <td align="center"><b>
[UTILS](#Utils)</td></tr>
<tr><td>

0. [ft_printf](#ft_printf)
</td><td>

1. [ft_putstr_fd](#ft_putstr_fd)
1. [ft_putchar_fd](#ft_putchar_fd)
1. [ft_putnbr_fd](#ft_putnbr_fd)
1. [ft_putnbr_base](#ft_putnbr_base)
</td></tr>
</tbody>
</table>

## Funciones Variádicas

En C, las funciones variádicas son funciones que pueden aceptar un número variable de argumentos. Estas funciones son útiles cuando no se conoce de antemano cuántos argumentos se van a pasar a la función. La biblioteca estándar de C proporciona un conjunto de macros y tipos de datos para manejar funciones variádicas, principalmente definidos en el encabezado <stdarg.h>.
Cómo Usar Funciones Variádicas en C

1. Incluir el Encabezado <stdarg.h>

Para trabajar con funciones variádicas, necesitas incluir el encabezado <stdarg.h>, que proporciona las herramientas necesarias.

2. Definir la Función Variádica

Para definir una función variádica, se utiliza una lista de argumentos fijos seguida de ... (tres puntos suspensivos) para indicar que la función puede recibir un número variable de argumentos.

``` c
void ejemploVariadico(int num_args, ...);
```

Aquí int num_args es un argumento fijo que indica cuántos argumentos adicionales se pasarán a la función.

3. Utilizar las Macros de <stdarg.h>

Dentro de la función, se utilizan macros específicas para manipular los argumentos variables:

- va_list: Define una variable de tipo va_list que será utilizada para acceder a los argumentos adicionales.

- va_start: Inicializa el objeto va_list para que apunte al primer argumento variádico. Debe ser llamado antes de acceder a cualquier argumento.

- va_arg: Accede a cada argumento adicional, especificando su tipo. Esta macro se utiliza dentro de un bucle para iterar sobre todos los argumentos.

- va_end: Limpia el objeto va_list una vez que se han procesado todos los argumentos. Debe ser llamada antes de que la función termine.

__Ejemplo Completo: Sumar Números Enteros__

``` c

#include <stdio.h>
#include <stdarg.h>

// Función variádica para sumar números enteros
int sumarEnteros(int num_args, ...) {
    int suma = 0;
    va_list args;

    // Inicializar la lista de argumentos
    va_start(args, num_args);

    // Iterar sobre los argumentos y sumarlos
    for (int i = 0; i < num_args; i++) {
        int numero = va_arg(args, int); // Obtener el siguiente argumento
        suma += numero;
    }

    // Limpiar la lista de argumentos
    va_end(args);

    return suma;
}

int main() {
    int resultado;

    // Llamar a la función con un número variable de argumentos
    resultado = sumarEnteros(3, 10, 20, 30);
    printf("La suma es: %d\n", resultado);

    resultado = sumarEnteros(5, 1, 2, 3, 4, 5);
    printf("La suma es: %d\n", resultado);

    return 0;
}

```

## Funciones del proyecto
## ft_printf

``` c
int	ft_printf(const char *s, ...)
```
Mediante una función variádica obtendremos una cadena como primer argumento. Dicha cadena hay que "parsearla", esto es encontrar cada % y el caracter siguiente que será el tipo de variable que necesitaremos convertir para imprimirla por pantalla. El número de argumentos restantes es indeterminado. El tipo tampoco lo sabremos por ello necesitamos obtener el siguiente caracter al % el cual nos dirá el tipo. Una vez sepamos el tipo, llamamos a la función que convierta ese número, cadena, etc, a caracteres imprimibles con **write**.

- %c Imprime un solo carácter.
- %s Imprime una string (como se define por efecto en C).
- %p El puntero void * dado como argumento se imprime en formato hexadecimal.
- %d Imprime un número decimal (base 10).
- %i Imprime un entero en base 10.
- %u Imprime un número decimal (base 10) sin signo.
- %x Imprime un número hexadecimal (base 16) en minúsculas.
- %X Imprime un número hexadecimal (base 16) en mayúsculas.
- % % para imprimir el símbolo del porcentaje.

# Utils

### ft_putstr_fd
``` c
int		ft_putstr_fd(char *s, int fd);
```
Función del libft que imprime por pantalla (fd = 1) una cadena de caracteres, devolviendo el número de caracteres imprimidos.


### ft_putchar_fd
``` c
int		ft_putchar_fd(unsigned char c, int fd);
```
Función del libft que imprime por pantalla (fd = 1) un caracter, devolviendo 1 si no ha habido un error, de lo contrario devuelve -1.

### ft_putnbr_fd
``` c
int		ft_putnbr_fd(int n, int fd);
```
Función del libft que imprime un número por pantalla (fd = 1), devolviendo 1 si no ha habido un error, de lo contrario devuelve -1. Para ello a su vez utiliza la función itoa. Está función se utilizará con los flag d e i, ya que son número con signo.

### ft_putnbr_base
``` c
int	ft_putnbr_base(char c, unsigned long nbr, char *base)
```
Función creada como ejercicio extra en la piscina. Muestra por pantalla cualquier número sin signo pasandole como parametro una determinada base. Está función se utilizará para imprimir números exadecimales, punteros, y usigned. Devulve el número de caracteres imprimidos o -1 si surje un error.

[$${\color{red}VOLVER}$$](../../README.md)
