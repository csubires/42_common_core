![Rating](/_assets/images/header.png)

# PUSH_SWAP [subject](es.push_swap.pdf)

### Indice de contenidos

## LIBRERÍA STACK
<table><tr>
	<th>MOVEMENTS_01.C</th>
	<th>MOVEMENTS_02.C</th>
</tr><tr>
</td><td>

- [ft_sa](#ft_sa)
- [ft_sb](#ft_sb)
- [ft_ss](#ft_ss)
- [ft_pa](#ft_pa)
- [ft_pb](#ft_pb)

</td><td>

- [ft_ra](#ft_ra)
- [ft_rb](#ft_rb)
- [ft_rr](#ft_rr)
- [ft_rra](#ft_rra)
- [ft_rrb](#ft_rrb)

</td></tr><tr>
	<th>MOVEMENTS_03.C</th>
	<th>STACK.C</th>
</tr><tr><td>

- [ft_rrr](#ft_rrr)
- [ft_show_ornot](#ft_show_ornot)
- [ft_print_error](#ft_print_error)
- [ft_threenodes](#ft_threenodes)

</td><td>

- [ft_stk_free](#ft_stk_free)
- [ft_new_node](#ft_new_node)
- [ft_stk_last](#ft_stk_last)
- [ft_stk_add](#ft_stk_add)
- [ft_stk_size](#ft_stk_size)

</td></tr><tr>
	<th>UTILS.C</th>
</tr><tr><td>

- [search_position](#search_position)
- [search_position_by](#search_position_by)
- [find_place](#find_place)
- [minmax](#minmax)
- [issorted](#issorted)

</td></tr></table>

## SOURCE

<table><tr>
	<th>FT_PARSE.C</th>
	<th>FT_ROTATE.C</th>
</tr><tr>
</td><td>

- [ft_free_split](#ft_free_split)
- [ft_check_duplicate](#ft_check_duplicate)
- [ft_str_parse](#ft_str_parse)
- [ft_parse](#ft_parse)

</td><td>

- [ft_rotate_rarb](#ft_rotate_rarb)
- [ft_rotate_rrarrb](#ft_rotate_rrarrb)
- [ft_rotate_rarrb](#ft_rotate_rarrb)
- [ft_rotate_rrarb](#ft_rotate_rrarb)
- [ft_min_rotates](#ft_min_rotates)

</td></tr><tr>
	<th>FT_CALCULATE.C</th>
	<th>FT_SORT.C</th>
</tr><tr><td>

- [ft_numof_rarb](#ft_numof_rarb)
- [ft_numof_rrarrb](#ft_numof_rrarrb)
- [ft_numof_rarrb](#ft_numof_rarrb)
- [ft_numof_rrarb](#ft_numof_rrarb)

</td><td>

- [ft_sort_b](#ft_sort_b)
- [ft_sort_a](#ft_sort_a)
- [ft_init_b](#ft_init_b)
- [ft_sort](#ft_sort)

</td></tr></table>

## BONUS

<table><tr>
	<th>CHECKER_BONUS.C</th>
</tr><tr>
</td><td>

- [ft_mov_ccc](#ft_mov_ccc)
- [ft_mov_cc](#ft_mov_cc)
- [ft_strcheck](#ft_strcheck)

</td></tr></table>

## Descripción

- Tienes 2 stacks, llamados a y b.
- El stack a contiene una cantidad aleatoria de números **positivos y/o negativos**, nunca duplicados.
- El stack b está vacío.
- El objetivo es ordenar los números del stack a en **orden ascendente**, con **el mínimo número de operaciones posible**.

## Restricciones
- Las variables globales están prohibidas.
- Debes escribir un programa llamado `push_swap` que recibirá como argumento el stack a con el formato de una lista de enteros. El primer argumento debe ser el que esté encima del stack (cuidado con el orden).
- El programa debe mostrar la lista de instrucciones más corta posible para ordenar el stack a, __de menor a mayor, donde el número menor se sitúe en la cima del stack__.
- Las instrucciones deben separarse utilizando un “\n” y nada más.
- Para una validación mínima del proyecto (que implica una nota mínima de 80), deberás ser capaz de ordenar 100 números aleatorios en menos de 700 operaciones.
- Para una validación máxima del proyecto y así poder obtener los bonus, deberás cumplir el primer paso anterior, pero también para 500 números aleatorios, no deberás superar las 5500 operaciones.

## Errores
> En caso de error, deberá mostrar Error seguido de un “\n” en la salida de errores estándar. Algunos de los posibles errores son:

- Argumentos que no son enteros
- Argumentos superiores a un número entero
- Y/O encontrar números duplicados.

## Bonus

Escribe un programa llamado checker

## Funcionamiento del algoritmo

	"Brevemente". El algoritmo empieza pasando 2 elementos de `a` hacia `b`, para tener una referencia de mínimo y máximo en el que ir ordenando los siguientes. Luego va pasando valores de la pila `a` a la `b` ordenandolos descendentemente para al final pasarlos a la pila `a` en orden ascendente y asegurandose que se pasan al lugar adecuado (más rotaciones), que es lo que pide el proyecto. Para ello busca el valor máximo en la pila `b`, para saber donde debe ir. Se pueden dar varios casos: que el valor máximo sea el primer elemento, el último elemento, o que este en medio. Una vez que se sepa en qué posición debería ir el número hay que rotar la pila para colocarlo en el lugar indicado. Dado que existen límites en los números de movimientos tanto para aprobar el proyecto como para aspirar al bonus, lo ideal es "simular" los movimientos antes de hacerlos, y quedarte con el que te de el mínimo número de movimientos. Todo por cada valor de la pila `a` calculando previamente los costes. Para ello calcula todas las posibles combinaciones de rotaciones que tiene que hacer para posicionar un número y coge el menor coste. Haciendo rotaciones al mismo tiempo ahorras movimientos, por lo tanto se penalizan las rotaciones simples. Después de una rotación se pasa un elemento de una pila a otra. Al final solo quedarán 3 elementos en el pila `a` que se ordenará con el mínimo coste posible, y a partir de ahí se irán pasando los elementeos de `b` a `a`, quedando `b` vacío. Aún queda comprobar si el número mínimo está en la cima de la pila `a` y si no es así se calcula que es mejor, si hacer rotaciones normales, o inversas para acabar con toda la pila ordenada.

## STACK LIBRARY

Para ordenar mejor el proyecto he decidio meter todas las funciones relacionadas con la manipulación de las pilas en una librería que se compilará con su propio Makefile en la carpeta `stack`.
También se hace uso de algunas funciones de mi propia librería `libft`.

### Estructura
``` c
typedef struct s_stack
{
	int				nbr;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;
```

### MOVEMENTS_01.C
#### ft_sa
``` c
void		ft_sa(t_stack **a, int show);

```
swap a: Intercambia los dos primeros elementos del stack a. No hace nada si hay uno o menos elementos.
#### ft_sb
``` c
void		ft_sb(t_stack **b, int show);

```
swap b: Intercambia los dos primeros elementos del stack b. No hace nada si hay uno o menos elementos.

#### ft_ss
``` c
void		ft_ss(t_stack **a, t_stack **b, int show);
```
swap a y swap b a la vez.

#### ft_pa
``` c
void		ft_pa(t_stack **a, t_stack **b, int show);
```
push a: Toma el primer elemento del stack b y lo pone el primero en el stack a. No hace nada si b está vacío.

#### ft_pb
``` c
void		ft_pb(t_stack **a, t_stack **b, int show);
```
push b: Toma el primer elemento del stack a y lo pone el primero en el stack b. No hace nada si a está vacío.

### MOVEMENTS_02.C
#### ft_ra
``` c
void		ft_ra(t_stack **a, int show);
```
rotate a: Desplaza hacia arriba todos los elementos del stack a una posición, de forma que el primer elemento se convierte en el último.

#### ft_rb
``` c
void		ft_rb(t_stack **b, int show);
```
rotate b: Desplaza hacia arriba todos los elementos del stack b una posición, de forma que el primer elemento se convierte en el último.

#### ft_rr
``` c
void		ft_rr(t_stack **a, t_stack **b, int show);
```
ra y rb al mismo tiempo.

#### ft_rra
``` c
void		ft_rra(t_stack **a, int show);
```
reverse rotate a: Desplaza hacia abajo todos los elementos del stack a una posición, de forma que el último elemento se convierte en el primero.

#### ft_rrb
``` c
void		ft_rrb(t_stack **b, int show);
```
reverse rotate b: Desplaza hacia abajo todos los elementos del stack b una posición, de forma que el último elemento se convierte en el primero. |


### MOVEMENTS_03.C
#### ft_rrr
``` c
void		ft_rrr(t_stack **a, t_stack **b, int show);
```
rra y rrb al mismo tiempo.

#### ft_show_ornot
``` c
void		ft_show_ornot(char *mov, int show);
```
Muestra o no el movimiento por pantalla dependiendo del argumento show.
Cuando el checker hace los movimientos no debe mostrarse, y cuando se hacen "combos" tampoco.

#### ft_print_error
``` c
void		ft_print_error(void);
```
Muestra "Error" seguido de un “\n” en la salida de errores estándar.

#### ft_threenodes
``` c
void		ft_threenodes(t_stack **s);
```
Ordena una pila cuando quedan 3 nodos en la pila `a`, con el número mínimo de movimientos.

### STACK.C
#### ft_stk_free
``` c
void		ft_stk_free(t_stack **s);
```
Libera toda la memória de una pila.

#### t_stack
``` c
t_stack		*ft_new_node(int nbr);
```
Crea un nuevo nodo de una pila con el número (nbr) dado.

#### t_stack
``` c
t_stack		*ft_stk_last(t_stack *s);
```
Devuelve el último nodo de una pila.

#### ft_stk_add
``` c
void		ft_stk_add(t_stack **s, t_stack *new);
```
Inserta un nodo al final de una pila (lista). Los números deben aparecer en la pila en el orden en el que se entrega.

#### ft_stk_size
``` c
int			ft_stk_size(t_stack *s);
```
Devuelve el número de nodos de la pila.

### UTILS.C
#### ft_search_nbr
``` c
int			ft_search_nbr(t_stack *s, int nbr);
```
Busca la posición de un número específico en una pila y devuelve la posición relativa de dicho número.

#### ft_orderly_place
``` c
int			ft_orderly_place(t_stack *s, int nbr, int aorb);
```
Busca la posición donde un número (nbr) debería insertarse en una pila (s) para estar ordenada.
aorb: según sea a o b se busca la posición para insertar de manera ascendente o descendente respectivamente.

#### ft_best_place
``` c
int			ft_best_place(t_stack *s, int nbr, int aorb);
```
Si aorb es 'b' y nbr está entre el primer elemento de la pila (s->nbr) y el último elemento (ft_stk_last(s)->nbr), o si aorb es 'a' y nbr está entre el primer y el último elemento pero en orden inverso, se establece x en 0, que indica que el elemento debería insertarle encima de la pila.

Si aorb es 'a' y nbr es mayor que el máximo (ft_minmax(s, 1)) o menor que el mínimo (ft_minmax(s, 0)), se busca la posición del mínimo en la pila con ft_search_nbr(s, ft_minmax(s, 0)).

Si aorb es 'b' y nbr es mayor que el máximo o menor que el mínimo, se busca la posición del máximo en la pila con ft_search_nbr(s, ft_minmax(s, 1)).

Si no se cumplen las condiciones anteriores, se busca la mejor posición para nbr utilizando la función ft_orderly_place.

La función ft_best_place es crucial para determinar la posición óptima de inserción de un número en una pila, manteniendo el orden según el contexto definido por aorb.

#### ft_minmax
``` c
int			ft_minmax(t_stack *s, int minormax);
```
Devuelve el valor mínimo o máximo de una pila dependiendo de si minormax es 0 o 1 respectivamente.

#### ft_issorted
``` c
int			ft_issorted(t_stack *s);

```
Comprueba que la pila esté ordenada y devuelve 1 si lo está.

## SOURCE

### FT_PARSE.C

```c
void	ft_free_split(char **arr);
```
Libera la memoria de la función split (array de punteros que apuntan cada uno a un string [array de caracteres]).

```c
int		ft_check_duplicate(t_stack *a);
```
Comprueba mediante un doble bucle que un número no está repetido en la pila.

```c
t_stack	*ft_str_parse(char *str, int *error);
```
Divide una cadena de números y los convierte a enteros comprobando que los valores no se sobrepasen de lo permitido en un tipo int. Si todo va bien devuelve la pila llena con los números.

```c
t_stack	*ft_parse(int argc, char *argv[]);
```
Si hay 2 argumentos significa que la colección de números se ha pasado como un string y por tanto hay que procesar la cadena __ft_str_parse__. En otro caso se presupone que los números son pasados como argumentos individuales, y pasa directamente a comprobar que son válidos.

### FT_ROTATE.C
#### ft_rotate_xxxx
``` c
int		ft_rotate_rarb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rarrb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rrarb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rrarrb(t_stack **a, t_stack **b, int nbr, char aorb);
```
La función ft_rotate_xxx se encarga de mover un número (nbr) desde una pila (a o b) a la otra, rotando ambas pilas simultáneamente o por separado según sea necesario para que el número nbr esté en la posición correcta en la pila de destino. El parámetro aorb indica en qué pila está inicialmente el número nbr.

Mientras el número en la cima de a no sea nbr y ft_best_place(*b, nbr, 'b') sea mayor que 0 indicando que nbr no está en la posición correcta, se rota ambas pilas hacia arriba simultáneamente con ft_rr(a, b, 1).

Si el número en la cima de a aún no es nbr, se rota solo a hacia arriba hasta que nbr esté en la cima.

Si nbr no está en la posición correcta, se rota solo la pila destino hacia arriba con hasta que nbr pueda ser insertado en la posición correcta.

Finalmente, se mueve nbr de una pila a otra.

#### ft_min_rotates
``` c
int		ft_min_rotates(t_stack *a, t_stack *b, char aorb);
```
Devuelve el número mínimo de rotaciones posibles de cada una de las combinaciones posibles de rotaciones.

### FT_CALCULATE.C
#### ft_numof_xxxx
``` c
int		ft_numof_rarb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rrarrb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rarrb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rrarb(t_stack *s1, t_stack *s2, int nbr, char aorb);
```
La función ft_numof_xxxx se encarga de determinar el número de rotaciones necesarias para mover un número (nbr) desde una pila (s1 o s2) a otra, asegurando que el número llegue a la posición correcta en la pila de destino. La función toma en cuenta la mejor posición para insertar el número y la cantidad de rotaciones necesarias para poner nbr en la cima de la pila origen.

Si la cantidad de rotaciones calculada para s1 es menor que la cantidad de rotaciones necesarias para poner nbr en la cima de s2 (calculada con ft_search_nbr), se actualiza x con este último valor. Esto asegura que x será el mínimo número de rotaciones necesarias entre las dos pilas.

### SORT

#### ft_sort_b
``` c
void	ft_sort_b(t_stack **a, t_stack **b);
```
Hace el ordenado desde `a` hacia `b`.

#### ft_sort_a
``` c
t_stack	**ft_sort_a(t_stack **a, t_stack **b);
```
Hace el ordenado desde `b` hacia `a`.

#### ft_init_b
``` c
t_stack	*ft_init_b(t_stack **a);
```
Inicializa la pila `b` e inicia el ordenado de elementos desde `a`, hacia `b`.

#### ft_sort
``` c
void	ft_sort(t_stack **a);
```
Inicia el ordenado si es necesario.


## BONUS
El bonus simplemente es la creación de un programa al cual le pasas por un lado las intruciones y por otro los elementos de la pila a los que se van a aplicar. Si una vez aplicado la pila resultar estar ordenada se imprimirá OK de lo contrario KAO.

### CHECKER_BONUS.C

#### ft_mov_ccc
``` c
void	ft_mov_ccc(t_stack **a, t_stack **b, char *str);
```
Realiza movimientos rr sobre una pila.

#### ft_mov_cc
``` c
char	*ft_mov_cc(t_stack **a, t_stack **b, char *str)
```
Realiza movimientos sobre una pila.

#### ft_strcheck
``` c
void	ft_strcheck(t_stack **a, t_stack **b, char *str)
```

<div style='text-align: right;'>

[UP &#11014;](#BONUS)
</div>

<div style='text-align: right;'>

[UP &#11014;](<#stack-library>)
</div>


# Algunos ejemplos para checkear

``` bash
ARG="6 1 -2147483648 2 0 2147483647"; ./push_swap $ARG | wc -l

./push_swap "6 1 -2147483648 2 0 2147483647" | ./checker_linux "6 1 -2147483648 2 0 2147483647"

echo "pb
ra
pb
ra
sa
ra
pa
pa" | ./checker 0 9 1 8 2

./push_swap 42
./push_swap 2 3
./push_swap 0 1 2 3
./push_swap 0 1 2 3 4 5 6 7 8
./push_swap 0 1 2 33 45 73 87

ARG="2 1 0"; ./push_swap $ARG | ./checker $ARG
ARG="'Between 0 and 3 randomly values chosen'"; ./push_swap
$ARG | ./checker $ARG

./push_swap 3 4 22 1

echo "pb
rra
ra
pa
rra" | ./checker 3 4 22 1

echo "rra
pb
sa
rra
pa
" | ./checker 3 2 1 0

echo "sa
pb
rrr" | ./checker 0 9 1 8 2 7 3 6 4 5

echo "sa\npb\nrrr" | ./checker 0 9 1 8 2 7 3 6 4 5

./checker 0 1 2

echo "pb\nra\npb\nra\nsa\nra\npa\npa" | ./checker 0 9 1 8 2

ARG="667 -6493 -9456 -4915 -9222 4472 4774 3842 -2836 -8942 -1556 6166 7063 -3877 -7372 9874 7480 -4153 -8680 5797 -7370 -3018 2084 3970 -607 3517 3052 6994 4906 -6519 -5233 6186 -7682 -3994 -2643 2800 -6012 1862 -7 -5153 2050 -7093 -7083 1970 -7085 -8930 8205 3204 3235 6339 -3132 -8360 -6453 7027 1084 7420 6807 6063 -7028 476 -8241 -2913 -1529 1441 644 4223 4716 9682 8239 9748 7345 3466 1150 -1989 4860 -154 5694 -6364 -659 -5875 6045 -5684 2450 5442 548 3390 -8313 -4628 -3382 -6954 -8871 -5681 9054 4942 -8103 -5530 3536 1736 4118 -2450"; ./push_swap $ARG | wc -l

ARG="81 41 91 19 48 34 59 9 63 24 36 4 -57 26 53 66 77 21 51 76 75 92 28 78 43 86 83 94 6 80 82 90 45 67 16 46 95 62 52 20 7 49 85 2 73 72 100 74 18 33 27 64 50 29 99 54 1 70 97 8 31 98 17 65 47 30 38 84 96 69 35 22 37 10 56 87 60 89 12 3 23 61 44 5 32 55 15 79 40 88 93 58 71 13 25 42 14 68 11 -39"; ./push_swap $ARG | wc -l

ARG="81 41 91 19 48 34 59 9 63 24 36 4 -57 26 53 66 77 21 51 76 75 92 28 78 43 86 83 94 6 80 82 90 45 67 16 46 95 62 52 20 7 49 85 2 73 72 100 74 18 33 27 64 50 29 99 54 1 70 97 8 31 98 17 65 47 30 38 84 96 69 35 22 37 10 56 87 60 89 12 3 23 61 44 5 32 55 15 79 40 88 93 58 71 13 25 42 14 68 11 -39"; ./push_swap $ARG | ./checker_linux $ARG

ARG="53 291 43 450 491 556 364 435 42 706 502 255 868 210 698 432 499 787 990 98 639 726 67 485 831 907 479 867 272 524 112 82 821 561 506 452 699 645 405 581 866 993 780 275 982 980 886 352 717 998 99 934 936 669 362 703 410 844 792 385 776 303 243 932 905 294 666 882 950 476 714 763 892 701 400 945 773 577 310 647 399 309 158 830 995 296 938 257 304 805 806 249 861 804 293 164 728 182 816 659 788 266 483 193 116 584 724 166 762 305 902 143 259 367 833 151 235 636 855 723 60 1 512 298 486 707 383 23 711 415 505 194 869 8 612 324 167 760 176 930 159 336 122 387 110 284 13 716 48 975 809 712 45 46 745 9 611 870 935 337 531 168 999 226 783 503 457 152 88 354 22 536 827 14 113 369 107 722 766 845 534 79 774 244 134 433 509 187 261 437 880 214 526 891 732 51 539 925 196 346 128 6 700 655 960 956 702 729 438 251 594 592 233 620 390 808 492 758 498 140 836 465 878 582 610 375 118 234 33 550 675 77 533 467 597 39 738 537 681 983 906 469 443 174 781 997 552 373 319 910 569 693 2 542 85 124 793 802 238 265 65 933 273 215 488 388 382 875 378 625 591 772 68 797 357 710 96 507 62 879 618 750 549 613 851 605 519 366 941 340 629 149 188 146 810 840 427 332 874 91 785 500 551 453 842 522 242 471 173 850 948 178 540 713 972 684 139 572 58 278 553 16 138 126 157 108 300 857 673 911 444 56 308 129 93 343 386 848 409 282 595 256 643 946 871 359 790 695 102 849 940 216 339 587 917 70 127 523 963 172 72 198 600 731 575 971 795 281 263 312 285 431 230 4 815 764 628 411 133 580 825 154 568 800 3 853 21 406 593 770 965 264 165 786 943 61 322 360 86 480 247 796 730 377 47 986 740 57 80 690 365 190 460 78 487 428 434 970 607 245 725 407 115 76 939 677 83 412 229 175 757 817 73 626 621 746 651 50 313 325 898 280 968 856 904 658 896 252 759 976 150 317 687 744 708 609 921 847 567 241 638 667 276 440 94 664 211 199 141 627 445 929 189 448 513 374 504 735 859 969 665 909 741 994 358 989 347 912 342 489 889 135 885 316 145 490 236 28 709 301"; ./push_swap $ARG | ./checker_linux $ARG

ARG="53 291 43 450 491 556 364 435 42 706 502 255 868 210 698 432 499 787 990 98 639 726 67 485 831 907 479 867 272 524 112 82 821 561 506 452 699 645 405 581 866 993 780 275 982 980 886 352 717 998 99 934 936 669 362 703 410 844 792 385 776 303 243 932 905 294 666 882 950 476 714 763 892 701 400 945 773 577 310 647 399 309 158 830 995 296 938 257 304 805 806 249 861 804 293 164 728 182 816 659 788 266 483 193 116 584 724 166 762 305 902 143 259 367 833 151 235 636 855 723 60 1 512 298 486 707 383 23 711 415 505 194 869 8 612 324 167 760 176 930 159 336 122 387 110 284 13 716 48 975 809 712 45 46 745 9 611 870 935 337 531 168 999 226 783 503 457 152 88 354 22 536 827 14 113 369 107 722 766 845 534 79 774 244 134 433 509 187 261 437 880 214 526 891 732 51 539 925 196 346 128 6 700 655 960 956 702 729 438 251 594 592 233 620 390 808 492 758 498 140 836 465 878 582 610 375 118 234 33 550 675 77 533 467 597 39 738 537 681 983 906 469 443 174 781 997 552 373 319 910 569 693 2 542 85 124 793 802 238 265 65 933 273 215 488 388 382 875 378 625 591 772 68 797 357 710 96 507 62 879 618 750 5 49 613 851 605 519 366 941 340 629 149 188 146 810 840 427 332 874 91 785 500 551 453 842 522 242 471 173 850 948 178 540 713 972 684 139 572 58 278 553 16 138 126 157 108 300 857 673 911 444 56 308 129 93 343 386 848 409 282 595 256 643 946 871 359 790 695 102 849 940 216 339 587 917 70 127 523 963 172 72 198 600 731 575 971 795 281 263 312 285 431 230 4 815 764 628 411 133 580 825 154 568 800 3 853 21 406 593 770 965 264 165 786 943 61 322 360 86 480 247 796 730 377 47 986 740 57 80 690 365 190 460 78 487 428 434 970 607 245 725 407 115 76 939 677 83 412 229 175 757 817 73 626 621 746 651 50 313 325 898 280 968 856 904 658 896 252 759 976 150 317 687 744 708 609 921 847 567 241 638 667 276 440 94 664 211 199 141 627 445 929 189 448 513 374 504 735 859 969 665 909 741 994 358 989 347 912 342 489 889 135 885 316 145 490 236 28 709 301"; ./push_swap $ARG | wc -l
```

## Herramientas
- [Visualizador de push_swap](https://github.com/o-reo/push_swap_visualizer)
- [Generador de números](https://www.calculatorsoup.com/calculators/statistics/random-number-generator.php)

[$${\color{red}VOLVER}$$](../../README.md)
