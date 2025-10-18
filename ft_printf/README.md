
```markdown
![Rating](/_assets/images/header.png)

# FT_PRINTF [subject](es.printf.pdf)

<table align="center">
<caption>Table of Contents</caption>
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

## Variadic Functions

In C, variadic functions are functions that can accept a variable number of arguments. These functions are useful when you don't know in advance how many arguments will be passed to the function. The C standard library provides a set of macros and data types to handle variadic functions, mainly defined in the <stdarg.h> header.
How to Use Variadic Functions in C

1. Include the <stdarg.h> Header

To work with variadic functions, you need to include the <stdarg.h> header, which provides the necessary tools.

2. Define the Variadic Function

To define a variadic function, use a fixed argument list followed by ... (three dots) to indicate that the function can receive a variable number of arguments.

``` c
void exampleVariadic(int num_args, ...);
```

Here int num_args is a fixed argument that indicates how many additional arguments will be passed to the function.

3. Use the <stdarg.h> Macros

Inside the function, use specific macros to manipulate the variable arguments:

- va_list: Defines a variable of type va_list that will be used to access the additional arguments.

- va_start: Initializes the va_list object to point to the first variadic argument. Must be called before accessing any argument.

- va_arg: Accesses each additional argument, specifying its type. This macro is used within a loop to iterate over all arguments.

- va_end: Cleans up the va_list object once all arguments have been processed. Must be called before the function ends.

__Complete Example: Sum Integers__

``` c

#include <stdio.h>
#include <stdarg.h>

// Variadic function to sum integers
int sumIntegers(int num_args, ...) {
    int sum = 0;
    va_list args;

    // Initialize the argument list
    va_start(args, num_args);

    // Iterate over the arguments and sum them
    for (int i = 0; i < num_args; i++) {
        int number = va_arg(args, int); // Get the next argument
        sum += number;
    }

    // Clean up the argument list
    va_end(args);

    return sum;
}

int main() {
    int result;

    // Call the function with a variable number of arguments
    result = sumIntegers(3, 10, 20, 30);
    printf("The sum is: %d\n", result);

    result = sumIntegers(5, 1, 2, 3, 4, 5);
    printf("The sum is: %d\n", result);

    return 0;
}

```

## Project Functions
## ft_printf

``` c
int	ft_printf(const char *s, ...)
```
Using a variadic function we get a string as the first argument. This string needs to be "parsed", meaning finding each % and the following character which will be the type of variable we need to convert to print it on screen. The number of remaining arguments is undetermined. The type is also unknown, so we need to get the character following the % which will tell us the type. Once we know the type, we call the function that converts that number, string, etc., to printable characters with **write**.

- %c Prints a single character.
- %s Prints a string (as defined by default in C).
- %p The void * pointer given as argument is printed in hexadecimal format.
- %d Prints a decimal number (base 10).
- %i Prints an integer in base 10.
- %u Prints an unsigned decimal number (base 10).
- %x Prints a hexadecimal number (base 16) in lowercase.
- %X Prints a hexadecimal number (base 16) in uppercase.
- % % to print the percentage symbol.

# Utils

### ft_putstr_fd
``` c
int		ft_putstr_fd(char *s, int fd);
```
Libft function that prints a string of characters to the screen (fd = 1), returning the number of characters printed.

### ft_putchar_fd
``` c
int		ft_putchar_fd(unsigned char c, int fd);
```
Libft function that prints a character to the screen (fd = 1), returning 1 if there was no error, otherwise returns -1.

### ft_putnbr_fd
``` c
int		ft_putnbr_fd(int n, int fd);
```
Libft function that prints a number to the screen (fd = 1), returning 1 if there was no error, otherwise returns -1. For this, it uses the itoa function. This function will be used with the d and i flags, since they are signed numbers.

### ft_putnbr_base
``` c
int	ft_putnbr_base(char c, unsigned long nbr, char *base)
```
Function created as an extra exercise in the piscine. Displays any unsigned number on screen by passing a specific base as parameter. This function will be used to print hexadecimal numbers, pointers, and unsigned numbers. Returns the number of characters printed or -1 if an error occurs.

[$${\color{red}BACK$$}$$](../../README.md)
```
