/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:48:51 by csubires          #+#    #+#             */
/*   Updated: 2024/08/27 11:34:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../source/push_swap.h"
#include "../libft/libft.h"
#include "../stack/stack.h"

// clang main.c obj/ft_parse.o obj/ft_rotate.o obj/ft_calculate.o obj/ft_sort.o -L. -l:libft/libft.a -l:stack/stack.a -o obj/main.out

//	######################## STACK

//	MOVEMENTS_01.C
void	test_00_ft_sa();
void	test_01_ft_sb();
void	test_02_ft_ss();
void	test_03_ft_pa();
void	test_04_ft_pb();

//	MOVEMENTS_02.C
void	test_05_ft_ra();
void	test_06_ft_rb();
void	test_07_ft_rr();
void	test_08_ft_rra();
void	test_09_ft_rrb();

//	MOVEMENTS_03.C
void	test_10_ft_rrr();
void	test_11_ft_show_ornot();
void	test_12_ft_print_error();

//	STACK.C
void	test_13_ft_stk_free();
void	test_14_ft_new_node();
void	test_15_ft_stk_last();
void	test_16_ft_stk_add();
void	test_17_ft_stk_size();

//	UTILS.C
void	test_18_ft_search_nbr();
void	test_18_ft_orderly_place();
void	test_19_ft_best_place();
void	test_20_ft_minmax();

//	######################## SOURCE

//	FT_PARSE.C
void	test_21_ft_check_duplicate();
void	test_22_ft_parse();

//	FT_ROTATE.C
void	test_23_ft_rotate_rarb();
void	test_24_ft_rotate_rarrb();
void	test_25_ft_rotate_rrarb();
void	test_26_ft_rotate_rrarrb();
void	test_27_ft_rotate();

//	ft_calculate.C
void	test_28_ft_numof_rarb();
void	test_29_ft_numof_rrarrb();
void	test_30_ft_numof_rarrb();
void	test_31_ft_numof_rrarb();
void	test_32_ft_issorted();

//	FT_SORT.C
void	test_33_ft_init_b();
void	test_34_ft_sort_a();
void	test_35_ft_threenodes();

void	test_36_ft_sort();

//	######################## BONUS

//	PUSH_SWAP_BONUS.C
void	test_37_ft_mov_cc();

//	AUXILIARY
void	tester_all();
t_stack	*initialize_A();
t_stack	*initialize_B();
t_stack	*initializethree_AB();
void	stkprint(t_stack **s, char *str);

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{	char *arg = argv[1];
		//printf("\e[1;1H\e[2J");
				printf("\n OPTION SELECTED: %s", arg);
		if (strcmp(arg, "00") == 0 || strcmp(arg, "ft_sa") == 0)	 				{ test_00_ft_sa(); }
		else if (strcmp(arg, "01") == 0 || strcmp(arg, "ft_sb") == 0)	 			{ test_01_ft_sb(); }
		else if (strcmp(arg, "02") == 0 || strcmp(arg, "ft_ss") == 0)	 			{ test_02_ft_ss(); }
		else if (strcmp(arg, "03") == 0 || strcmp(arg, "ft_pa") == 0)	 			{ test_03_ft_pa(); }
		else if (strcmp(arg, "04") == 0 || strcmp(arg, "ft_pb") == 0)	 			{ test_04_ft_pb(); }
		else if (strcmp(arg, "05") == 0 || strcmp(arg, "ft_ra") == 0)	 			{ test_05_ft_ra(); }
		else if (strcmp(arg, "06") == 0 || strcmp(arg, "ft_rb") == 0)	 			{ test_06_ft_rb(); }
		else if (strcmp(arg, "07") == 0 || strcmp(arg, "ft_rr") == 0)	 			{ test_07_ft_rr(); }
		else if (strcmp(arg, "08") == 0 || strcmp(arg, "ft_rra") == 0)	 			{ test_08_ft_rra(); }
		else if (strcmp(arg, "09") == 0 || strcmp(arg, "ft_rrb") == 0)	 			{ test_09_ft_rrb(); }
		else if (strcmp(arg, "10") == 0 || strcmp(arg, "ft_rrr") == 0)	 			{ test_10_ft_rrr(); }
		else if (strcmp(arg, "11") == 0 || strcmp(arg, "ft_show_ornot") == 0)	 	{ test_11_ft_show_ornot(); }
		else if (strcmp(arg, "12") == 0 || strcmp(arg, "ft_print_error") == 0)	 	{ test_12_ft_print_error(); }
		else if (strcmp(arg, "13") == 0 || strcmp(arg, "ft_stk_free") == 0)	 		{ test_13_ft_stk_free(); }
		else if (strcmp(arg, "14") == 0 || strcmp(arg, "ft_new_node") == 0)	 		{ test_14_ft_new_node(); }
		else if (strcmp(arg, "15") == 0 || strcmp(arg, "ft_stk_last") == 0)	 		{ test_15_ft_stk_last(); }
		else if (strcmp(arg, "16") == 0 || strcmp(arg, "ft_stk_add") == 0)	 	{ test_16_ft_stk_add(); }
		else if (strcmp(arg, "17") == 0 || strcmp(arg, "ft_stk_size") == 0)	 		{ test_17_ft_stk_size(); }
		else if (strcmp(arg, "18") == 0 || strcmp(arg, "ft_search_nbr") == 0)	{ test_18_ft_search_nbr(); }
		else if (strcmp(arg, "18") == 0 || strcmp(arg, "ft_orderly_place") == 0)	{ test_18_ft_orderly_place(); }
		else if (strcmp(arg, "19") == 0 || strcmp(arg, "ft_best_place") == 0)	 	{ test_19_ft_best_place(); }
		else if (strcmp(arg, "20") == 0 || strcmp(arg, "ft_minmax") == 0)	 		{ test_20_ft_minmax(); }
		else if (strcmp(arg, "21") == 0 || strcmp(arg, "ft_check_duplicate") == 0)	 		{ test_21_ft_check_duplicate(); }
		else if (strcmp(arg, "22") == 0 || strcmp(arg, "ft_parse") == 0)	 		{ test_22_ft_parse(); }
		else if (strcmp(arg, "23") == 0 || strcmp(arg, "ft_rotate_rarb") == 0)	 	{ test_23_ft_rotate_rarb(); }
		else if (strcmp(arg, "24") == 0 || strcmp(arg, "ft_rotate_rarrb") == 0)	 	{ test_24_ft_rotate_rarrb(); }
		else if (strcmp(arg, "25") == 0 || strcmp(arg, "ft_rotate_rrarb") == 0)	 	{ test_25_ft_rotate_rrarb(); }
		else if (strcmp(arg, "26") == 0 || strcmp(arg, "ft_rotate_rrarrb") == 0)	{ test_26_ft_rotate_rrarrb(); }
		else if (strcmp(arg, "27") == 0 || strcmp(arg, "ft_rotate") == 0)	 		{ test_27_ft_rotate(); }
		else if (strcmp(arg, "28") == 0 || strcmp(arg, "ft_numof_rarb") == 0)	 	{ test_28_ft_numof_rarb(); }
		else if (strcmp(arg, "29") == 0 || strcmp(arg, "ft_numof_rrarrb") == 0)	{ test_29_ft_numof_rrarrb(); }
		else if (strcmp(arg, "30") == 0 || strcmp(arg, "ft_numof_rarrb") == 0)	 	{ test_30_ft_numof_rarrb(); }
		else if (strcmp(arg, "31") == 0 || strcmp(arg, "ft_numof_rrarb") == 0)	 	{ test_31_ft_numof_rrarb(); }
		else if (strcmp(arg, "32") == 0 || strcmp(arg, "ft_issorted") == 0)	 	{ test_32_ft_issorted(); }
		else if (strcmp(arg, "33") == 0 || strcmp(arg, "ft_init_b") == 0)	 		{ test_33_ft_init_b(); }
		else if (strcmp(arg, "34") == 0 || strcmp(arg, "ft_sort_a") == 0)	 		{ test_34_ft_sort_a(); }
		else if (strcmp(arg, "35") == 0 || strcmp(arg, "ft_threenodes") == 0)	 	{ test_35_ft_threenodes(); }
		else if (strcmp(arg, "36") == 0 || strcmp(arg, "ft_sort") == 0)	 			{ test_36_ft_sort(); }
		else if (strcmp(arg, "37") == 0 || strcmp(arg, "ft_mov_cc") == 0)	 		{ test_37_ft_mov_cc(); }
		else if (strcmp(arg, "99") == 0 || strcmp(arg, "all") == 0)	 		{ tester_all(); }
		else { printf("¡ ERROR : FUNCTION \"%s\" NOT FOUND!\n", arg); }
	}
	return (0);
}

void test_00_ft_sa()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 00 - TESTING FT_SA \e[0m\n");
	printf("sa swap a: Intercambia los dos primeros elementos del stack a. No hace nada si hay uno o menos elementos.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------_B------
	stkprint(&a, "STACK A -> \t\t");
	ft_sa(&a, 0);
	stkprint(&a, "STACK A (FT_SA) -> \t");
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_01_ft_sb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 01 - TESTING FT_SB \e[0m\n");
	printf("sb swap b: Intercambia los dos primeros elementos del stack b. No hace nada si hay uno o menos elementos.\n\t");
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&b, "STACK B -> \t");
	ft_sb(&b, 0);
	stkprint(&b, "STACK B (FT_SB) -> \t");
	// --------------------------
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_02_ft_ss()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 02 - TESTING FT_SS \e[0m\n");
	printf("ss swap a y swap b a la vez.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_ss(&a, &b, 0);
	stkprint(&a, "STACK A (FT_SS) -> \t");
	stkprint(&b, "STACK B (FT_SS) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_03_ft_pa()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 03 - TESTING FT_PA \e[0m\n");
	printf("pa push a: Toma el primer elemento del stack b y lo pone el primero en el stack a. No hace nada si b está vacío.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_pa(&a, &b, 0);
	stkprint(&a, "STACK A (FT_PA) -> \t");
	stkprint(&b, "STACK B (FT_PA) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_04_ft_pb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 04 - TESTING FT_PB \e[0m\n");
	printf("pb push b: Toma el primer elemento del stack a y lo pone el primero en el stack b. No hace nada si a está vacío.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_pb(&a, &b, 0);
	stkprint(&a, "STACK A (FT_PB) -> \t");
	stkprint(&b, "STACK B (FT_PB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_05_ft_ra()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 05 - TESTING FT_RA \e[0m\n");
	printf("ra rotate a: Desplaza hacia arriba todos los elementos del stack a una posición, de forma que el primer elemento se convierte en el último\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	ft_ra(&a, 0);
	stkprint(&a, "STACK A (FT_RA) -> \t");
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_06_ft_rb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 06 - TESTING FT_RB \e[0m\n");
	printf("rb rotate b: Desplaza hacia arriba todos los elementos del stack b una posición, de forma que el primer elemento se convierte en el último.\n");
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&b, "STACK B -> \t\t");
	ft_rb(&b, 0);
	stkprint(&b, "STACK B (FT_RB) -> \t");
	// --------------------------
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_07_ft_rr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 07 - TESTING FT_RR \e[0m\n");
	printf("ra y rb al mismo tiempo.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rr(&a, &b, 0);
	stkprint(&a, "STACK A (FT_RR) -> \t");
	stkprint(&b, "STACK B (FT_RR) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_08_ft_rra()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 08 - TESTING FT_RRA \e[0m\n");
	printf("rra reverse rotate a: Desplaza hacia abajo todos los elementos del stack a una posición, de forma que el último elemento se convierte en el primero.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	ft_rra(&a, 0);
	stkprint(&a, "STACK A (FT_RRA) -> \t");
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_09_ft_rrb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 09 - TESTING FT_RRB \e[0m\n");
	printf("rrb reverse rotate b: Desplaza hacia abajo todos los elementos del stack b una posición, de forma que el último elemento se convierte en el primero.\n");
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&b, "STACK B -> \t\t");
	ft_rrb(&b, 0);
	stkprint(&b, "STACK B (FT_RRB) -> \t");
	// --------------------------
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_10_ft_rrr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 10 - TESTING FT_RRR \e[0m\n");
	printf("ra y rb al mismo tiempo.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rrr(&a, &b, 0);
	stkprint(&a, "STACK A (FT_RRR) -> \t");
	stkprint(&b, "STACK B (FT_RRR) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}

void test_11_ft_show_ornot()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 11 - ft_show_ornot \e[0m\n");
	printf("Muestra o no los movimientos.\n");
	//	CHECK CODE --------------
	ft_show_ornot("ft_show_ornot", 0);
	ft_show_ornot("ft_show_ornot", 1);
	// --------------------------
	printf("\n\n _________________________________________________________________");
}

void test_12_ft_print_error()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 12 - ft_print_error \e[0m\n");
	printf("Mostrar Error seguido de un “\n” en la salida de errores estándar.\n");
	//	CHECK CODE --------------
	printf("ft_print_error(); No lo ejecuto porque incluye un exit(1) :D\n");
	// --------------------------
	printf("\n\n _________________________________________________________________");
}

void test_13_ft_stk_free()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 13 - ft_stk_free \e[0m\n");
	printf("Liberar stack.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	ft_stk_free(&a);
	stkprint(&a, "STACK A (ft_stk_free) -> \t\t");
	// --------------------------
	printf("\n\n _________________________________________________________________");
}

void test_14_ft_new_node()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 14 - ft_new_node \e[0m\n");
	printf("Crea un nuevo nodo.\n");
	//	CHECK CODE --------------
	t_stack	*a = ft_new_node(999);
	stkprint(&a, "STACK A (ft_new_node) -> \t\t");
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_15_ft_stk_last()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 15 - ft_stk_last \e[0m\n");
	printf("Devuelve el último elemento de un stack.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	t_stack *last = ft_stk_last(a);
	stkprint(&a, "STACK A -> \t\t\t");
	printf("STACK A (ft_stk_last) -> \t%d", last->nbr);
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_16_ft_stk_add()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 16 - ft_stk_add \e[0m\n");
	printf("Añade un nodo al final de un stack.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	ft_stk_add(&a, ft_new_node(999));
	stkprint(&a, "STACK A (ft_stk_add)->");
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_17_ft_stk_size()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 17 - ft_stk_size \e[0m\n");
	printf("Devuelve el número de nodos de un stack.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t\t");
	int nbr = ft_stk_size(a);
	printf("STACK A (ft_stk_size) -> %d", nbr);
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_18_ft_search_nbr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 18 - ft_search_nbr \e[0m\n");
	printf("Devuelve la posición en la que encaja el valor X empezando en 0\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t\t");
	int nbr = ft_search_nbr(a, 34);
	printf("STACK A (ft_search_nbr) 34 -> %d", nbr);
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_18_ft_orderly_place()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 18 - ft_search_nbr \e[0m\n");
	printf("Devuelve la posición en la que está el valor X\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t\t");
	int nbr = ft_orderly_place(a, 34, 1);
	printf("STACK A (ft_search_nbr) 34 -> %d", nbr);
	stkprint(&a, "STACK B -> \t\t\t");
	nbr = ft_orderly_place(b, 8, 0);
	printf("STACK B (ft_search_nbr) 34 -> %d", nbr);
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________");
}


void test_19_ft_best_place()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 19 - ft_best_place \e[0m\n");
	printf("Devuelve la posición en la que poner meter un valor de forma ordenada X > Y\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	int nbr = ft_best_place(a, 3, 1);
	stkprint(&a, "STACK A -> \t\t\t");
	printf("STACK A (ft_best_place) 3 -> %d", nbr);
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_20_ft_minmax()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 20 - FT_MINMAX \e[0m\n");
	printf("Devuelve el valor mínimo o máximo de un stack.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	printf("STACK A (FT_MINMAX, 0) -> %d\n", ft_minmax(a, 0));
	printf("STACK A (FT_MINMAX, 1) -> %d", ft_minmax(a, 1));
	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_21_ft_check_duplicate()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 21 - ft_check_duplicate \e[0m\n");
	printf("Comprueba si hay valores duplicados.\n");
	t_stack	*a = initialize_A();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	printf("STACK A (ft_check_duplicate) -> %d\n", ft_check_duplicate(a));

	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________");
}

void test_22_ft_parse()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 22 - FT_PARSE \e[0m\n");

	t_stack	*a;
	t_stack	*b;
	printf("Convertir la cadena de enteros a números enteros.\n");
	//	CHECK CODE --------------
	char	*data00[4];
	data00[0] = "----";
	data00[1] = "-555555";
	data00[2] = "-33";
	data00[3] = "-1";
	char	*data01[4];
	data01[0] = "----";
	data01[1] = "8";
	data01[2] = "7777777";
	data01[3] = "1";
	a = ft_parse(4, data00);
	b = ft_parse(4, data01);
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);

	printf("\n\n _________________________________________________________________ TODO");
}

void test_23_ft_rotate_rarb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 23 - FT_ROTATE_RARB \e[0m\n");
	printf("Hace rb, Va rotando el stack a hasta encontrar un valor, lo saca y lo mete en b.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rarb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_24_ft_rotate_rarrb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 24 - FT_ROTATE_RARRB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rarrb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_25_ft_rotate_rrarb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 25 - FT_ROTATE_RRARB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rrarb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_26_ft_rotate_rrarrb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 26 - FT_ROTATE_RRARRB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rrarrb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_27_ft_rotate()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 27 - FT_ROTATE \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_28_ft_numof_rarb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 28 - ft_numof_RARB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rarb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_29_ft_numof_rrarrb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 29 - ft_numof_RRARRB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rrarrb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_30_ft_numof_rarrb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 30 - ft_numof_RARRB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rarrb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_31_ft_numof_rrarb()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 31 - ft_numof_RRARB \e[0m\n");
	printf("XXXXXXXXXXXXX.\n");
	t_stack	*a = initialize_A();
	t_stack	*b = initialize_B();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_rotate_rrarb(&a, &b, 34, 'a');
	stkprint(&a, "STACK A (FT_ROTATE_RARRB) -> \t");
	stkprint(&b, "STACK B (FT_ROTATE_RARRB) -> \t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_32_ft_issorted()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 32 - ft_issorted \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_33_ft_init_b()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 33 - ft_init_b \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_34_ft_sort_a()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 34 - FT_SORT_A \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_35_ft_threenodes()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 35 - ft_threenodes \e[0m\n");
	printf("Ordena ascendente o descente cuando sólo quedan 3 nodos.\n");
	t_stack	*a = initializethree_AB();
	t_stack	*b = initializethree_AB();
	//	CHECK CODE --------------
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	ft_threenodes(&a);
	ft_threenodes(&b);
	stkprint(&a, "STACK A -> \t\t");
	stkprint(&b, "STACK B -> \t\t");
	// --------------------------
	ft_stk_free(&a);
	ft_stk_free(&b);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_36_ft_sort()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 36 - TESTING FT_SORT \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void test_37_ft_mov_cc()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 37 - FT_MOV_CC \e[0m\n");
	t_stack	*a = initialize_A();

	//	CHECK CODE --------------



	// --------------------------
	ft_stk_free(&a);
	printf("\n\n _________________________________________________________________ TODO");
}

void tester_all()
{
	test_00_ft_sa();
	test_01_ft_sb();
	test_02_ft_ss();
	test_03_ft_pa();
	test_04_ft_pb();
	test_05_ft_ra();
	test_06_ft_rb();
	test_07_ft_rr();
	test_08_ft_rra();
	test_09_ft_rrb();
	test_10_ft_rrr();
	test_11_ft_show_ornot();
	test_12_ft_print_error();
	test_13_ft_stk_free();
	test_14_ft_new_node();
	test_15_ft_stk_last();
	test_16_ft_stk_add();
	test_17_ft_stk_size();
	test_18_ft_search_nbr();
	test_19_ft_best_place();
	test_20_ft_minmax();
	test_21_ft_check_duplicate();
	test_22_ft_parse();
	test_23_ft_rotate_rarb();
	test_24_ft_rotate_rarrb();
	test_25_ft_rotate_rrarb();
	test_26_ft_rotate_rrarrb();
	test_27_ft_rotate();
	test_28_ft_numof_rarb();
	test_29_ft_numof_rrarrb();
	test_30_ft_numof_rarrb();
	test_31_ft_numof_rrarb();
	test_32_ft_issorted();
	test_33_ft_init_b();
	test_34_ft_sort_a();
	test_35_ft_threenodes();
	test_36_ft_sort();
	test_37_ft_mov_cc();
}


// 	AUX

t_stack	*initializethree_AB()
{
	t_stack	*s;

	char	*data[4];
	data[0] = "----";
	data[1] = "8";
	data[2] = "33";
	data[3] = "1";

	s = ft_parse(4, data);
	if (!s || ft_check_duplicate(s))
	{
		ft_stk_free(&s);
		ft_print_error();
	}
	return (s);
}

t_stack	*initialize_A()
{
	t_stack	*a;

	char	*data[11];
	data[0] = "----";
	data[1] = "8";
	data[2] = "33";
	data[3] = "1";
	data[4] = "7";
	data[5] = "34";
	data[6] = "2";
	data[7] = "-567";
	data[8] = "0";
	data[9] = "11";
	data[10] = "5";

	a = ft_parse(11, data);
	if (!a || ft_check_duplicate(a))
	{
		ft_stk_free(&a);
		ft_print_error();
	}
	return (a);
}

t_stack	*initialize_B()
{
	t_stack	*b;

	char	*data[4];
	data[0] = "----";
	data[1] = "56";
	data[2] = "8";
	data[3] = "22";

	b = ft_parse(4, data);
	if (!b || ft_check_duplicate(b))
	{
		ft_stk_free(&b);
		ft_print_error();
	}
	return (b);
}


void	stkprint(t_stack **s, char *str)
{
	t_stack *tmp;

	tmp = *s;
	if (ft_stk_size(tmp) == 2)
		printf("Two elements IN STACK");
	else
	{
		printf("%s", str);
		while (tmp)
		{
			printf("%d, ", tmp->nbr);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
