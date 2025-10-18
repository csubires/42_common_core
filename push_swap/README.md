```markdown
![Rating](/_assets/images/header.png)

# PUSH_SWAP [subject](es.push_swap.pdf)

### Table of Contents

## STACK LIBRARY
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

## Description

- You have 2 stacks, called a and b.
- Stack a contains a random amount of **positive and/or negative** numbers, **never duplicates**.
- Stack b is empty.
- The goal is to sort the numbers in stack a in **ascending order**, with the **minimum number of operations possible**.

## Restrictions
- Global variables are prohibited.
- You must write a program called `push_swap` that will receive stack a as arguments in the format of a list of integers. The first argument should be the one at the top of the stack (be careful with the order).
- The program must display the shortest possible list of instructions to sort stack a, __from smallest to largest, where the smallest number is at the top of the stack__.
- Instructions must be separated using a "\n" and nothing else.
- For minimum project validation (which implies a minimum grade of 80), you must be able to sort 100 random numbers in less than 700 operations.
- For maximum project validation and to obtain bonuses, you must meet the previous step, but also for 500 random numbers, you must not exceed 5500 operations.

## Errors
> In case of error, it must display Error followed by a "\n" on the standard error output. Some possible errors are:

- Arguments that are not integers
- Arguments larger than an integer
- And/or finding duplicate numbers.

## Bonus

Write a program called checker

## Algorithm Operation

	"Briefly". The algorithm starts by moving 2 elements from `a` to `b`, to have a reference of minimum and maximum to sort the following ones. Then it moves values from stack `a` to `b` sorting them in descending order to finally move them to stack `a` in ascending order and ensuring they are placed in the correct position (more rotations), which is what the project requires. To do this, it finds the maximum value in stack `b` to know where it should go. Several cases can occur: the maximum value is the first element, the last element, or it's in the middle. Once the position where the number should go is known, the stack must be rotated to place it in the indicated position. Given the limits on the number of movements both to pass the project and to aspire for the bonus, the ideal is to "simulate" the movements before doing them, and keep the one that gives the minimum number of movements. All this for each value in stack `a` by pre-calculating the costs. To do this, it calculates all possible rotation combinations needed to position a number and takes the lowest cost. By doing rotations simultaneously, movements are saved, therefore simple rotations are penalized. After a rotation, an element is moved from one stack to another. At the end, only 3 elements will remain in stack `a` which will be sorted with the minimum possible cost, and then the elements from `b` will be moved to `a`, leaving `b` empty. It still remains to check if the minimum number is at the top of stack `a` and if not, it calculates what is better, to do normal rotations or reverse rotations to end with the entire stack sorted.

## STACK LIBRARY

To better organize the project, I decided to put all functions related to stack manipulation in a library that will be compiled with its own Makefile in the `stack` folder.
It also uses some functions from my own `libft` library.

### Structure
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
swap a: Swaps the first two elements of stack a. Does nothing if there is one or fewer elements.
#### ft_sb
``` c
void		ft_sb(t_stack **b, int show);

```
swap b: Swaps the first two elements of stack b. Does nothing if there is one or fewer elements.

#### ft_ss
``` c
void		ft_ss(t_stack **a, t_stack **b, int show);
```
swap a and swap b at the same time.

#### ft_pa
``` c
void		ft_pa(t_stack **a, t_stack **b, int show);
```
push a: Takes the first element from stack b and puts it first in stack a. Does nothing if b is empty.

#### ft_pb
``` c
void		ft_pb(t_stack **a, t_stack **b, int show);
```
push b: Takes the first element from stack a and puts it first in stack b. Does nothing if a is empty.

### MOVEMENTS_02.C
#### ft_ra
``` c
void		ft_ra(t_stack **a, int show);
```
rotate a: Shifts up all elements of stack a by one position, so the first element becomes the last.

#### ft_rb
``` c
void		ft_rb(t_stack **b, int show);
```
rotate b: Shifts up all elements of stack b by one position, so the first element becomes the last.

#### ft_rr
``` c
void		ft_rr(t_stack **a, t_stack **b, int show);
```
ra and rb at the same time.

#### ft_rra
``` c
void		ft_rra(t_stack **a, int show);
```
reverse rotate a: Shifts down all elements of stack a by one position, so the last element becomes the first.

#### ft_rrb
``` c
void		ft_rrb(t_stack **b, int show);
```
reverse rotate b: Shifts down all elements of stack b by one position, so the last element becomes the first. |

### MOVEMENTS_03.C
#### ft_rrr
``` c
void		ft_rrr(t_stack **a, t_stack **b, int show);
```
rra and rrb at the same time.

#### ft_show_ornot
``` c
void		ft_show_ornot(char *mov, int show);
```
Shows or doesn't show the movement on screen depending on the show argument.
When the checker performs movements, they should not be shown, and when "combos" are done either.

#### ft_print_error
``` c
void		ft_print_error(void);
```
Displays "Error" followed by a "\n" on the standard error output.

#### ft_threenodes
``` c
void		ft_threenodes(t_stack **s);
```
Sorts a stack when there are 3 nodes left in stack `a`, with the minimum number of movements.

### STACK.C
#### ft_stk_free
``` c
void		ft_stk_free(t_stack **s);
```
Frees all memory of a stack.

#### t_stack
``` c
t_stack		*ft_new_node(int nbr);
```
Creates a new stack node with the given number (nbr).

#### t_stack
``` c
t_stack		*ft_stk_last(t_stack *s);
```
Returns the last node of a stack.

#### ft_stk_add
``` c
void		ft_stk_add(t_stack **s, t_stack *new);
```
Inserts a node at the end of a stack (list). Numbers must appear in the stack in the order they are delivered.

#### ft_stk_size
``` c
int			ft_stk_size(t_stack *s);
```
Returns the number of nodes in the stack.

### UTILS.C
#### ft_search_nbr
``` c
int			ft_search_nbr(t_stack *s, int nbr);
```
Searches for the position of a specific number in a stack and returns the relative position of that number.

#### ft_orderly_place
``` c
int			ft_orderly_place(t_stack *s, int nbr, int aorb);
```
Finds the position where a number (nbr) should be inserted in a stack (s) to be sorted.
aorb: depending on whether it's a or b, it searches for the position to insert in ascending or descending order respectively.

#### ft_best_place
``` c
int			ft_best_place(t_stack *s, int nbr, int aorb);
```
If aorb is 'b' and nbr is between the first element of the stack (s->nbr) and the last element (ft_stk_last(s)->nbr), or if aorb is 'a' and nbr is between the first and last element but in reverse order, x is set to 0, indicating that the element should be inserted on top of the stack.

If aorb is 'a' and nbr is greater than the maximum (ft_minmax(s, 1)) or less than the minimum (ft_minmax(s, 0)), the position of the minimum in the stack is searched with ft_search_nbr(s, ft_minmax(s, 0)).

If aorb is 'b' and nbr is greater than the maximum or less than the minimum, the position of the maximum in the stack is searched with ft_search_nbr(s, ft_minmax(s, 1)).

If the above conditions are not met, the best position for nbr is searched using the ft_orderly_place function.

The ft_best_place function is crucial for determining the optimal insertion position of a number in a stack, maintaining order according to the context defined by aorb.

#### ft_minmax
``` c
int			ft_minmax(t_stack *s, int minormax);
```
Returns the minimum or maximum value of a stack depending on whether minormax is 0 or 1 respectively.

#### ft_issorted
``` c
int			ft_issorted(t_stack *s);

```
Checks if the stack is sorted and returns 1 if it is.

## SOURCE

### FT_PARSE.C

```c
void	ft_free_split(char **arr);
```
Frees the memory from the split function (array of pointers each pointing to a string [character array]).

```c
int		ft_check_duplicate(t_stack *a);
```
Checks using a double loop that a number is not repeated in the stack.

```c
t_stack	*ft_str_parse(char *str, int *error);
```
Splits a string of numbers and converts them to integers, checking that the values do not exceed what is allowed in an int type. If everything goes well, it returns the stack filled with the numbers.

```c
t_stack	*ft_parse(int argc, char *argv[]);
```
If there are 2 arguments, it means the collection of numbers was passed as a string and therefore the string must be processed __ft_str_parse__. Otherwise, it assumes the numbers are passed as individual arguments, and directly checks if they are valid.

### FT_ROTATE.C
#### ft_rotate_xxxx
``` c
int		ft_rotate_rarb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rarrb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rrarb(t_stack **a, t_stack **b, int nbr, char aorb);
int		ft_rotate_rrarrb(t_stack **a, t_stack **b, int nbr, char aorb);
```
The ft_rotate_xxx function is responsible for moving a number (nbr) from one stack (a or b) to the other, rotating both stacks simultaneously or separately as needed so that the number nbr is in the correct position in the destination stack. The aorb parameter indicates in which stack the number nbr is initially located.

While the number at the top of a is not nbr and ft_best_place(*b, nbr, 'b') is greater than 0 indicating that nbr is not in the correct position, both stacks are rotated upward simultaneously with ft_rr(a, b, 1).

If the number at the top of a is still not nbr, only a is rotated upward until nbr is at the top.

If nbr is not in the correct position, only the destination stack is rotated upward until nbr can be inserted in the correct position.

Finally, nbr is moved from one stack to the other.

#### ft_min_rotates
``` c
int		ft_min_rotates(t_stack *a, t_stack *b, char aorb);
```
Returns the minimum number of possible rotations from each of the possible rotation combinations.

### FT_CALCULATE.C
#### ft_numof_xxxx
``` c
int		ft_numof_rarb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rrarrb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rarrb(t_stack *s1, t_stack *s2, int nbr, char aorb);
int		ft_numof_rrarb(t_stack *s1, t_stack *s2, int nbr, char aorb);
```
The ft_numof_xxxx function is responsible for determining the number of rotations needed to move a number (nbr) from one stack (s1 or s2) to another, ensuring that the number reaches the correct position in the destination stack. The function takes into account the best position to insert the number and the number of rotations needed to put nbr at the top of the source stack.

If the calculated number of rotations for s1 is less than the number of rotations needed to put nbr at the top of s2 (calculated with ft_search_nbr), x is updated with this latter value. This ensures that x will be the minimum number of rotations needed between the two stacks.

### SORT

#### ft_sort_b
``` c
void	ft_sort_b(t_stack **a, t_stack **b);
```
Performs sorting from `a` to `b`.

#### ft_sort_a
``` c
t_stack	**ft_sort_a(t_stack **a, t_stack **b);
```
Performs sorting from `b` to `a`.

#### ft_init_b
``` c
t_stack	*ft_init_b(t_stack **a);
```
Initializes stack `b` and starts sorting elements from `a` to `b`.

#### ft_sort
``` c
void	ft_sort(t_stack **a);
```
Starts sorting if necessary.

## BONUS
The bonus is simply the creation of a program to which you pass on one side the instructions and on the other the stack elements to which they will be applied. If after application the resulting stack is sorted, it will print OK otherwise KO.

### CHECKER_BONUS.C

#### ft_mov_ccc
``` c
void	ft_mov_ccc(t_stack **a, t_stack **b, char *str);
```
Performs rr movements on a stack.

#### ft_mov_cc
``` c
char	*ft_mov_cc(t_stack **a, t_stack **b, char *str)
```
Performs movements on a stack.

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

# Some examples to check

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

## Tools
- [Push_swap visualizer](https://github.com/o-reo/push_swap_visualizer)
- [Number generator](https://www.calculatorsoup.com/calculators/statistics/random-number-generator.php)

[$${\color{red}BACK}$$](../../README.md)
```
