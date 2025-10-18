/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:01:35 by csubires          #+#    #+#             */
/*   Updated: 2024/08/27 10:19:47 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../ft_printf.h"

void	test_00_ft_printf();

int	main(void)
{
	//printf("\e[1;1H\e[2J");
	test_00_ft_printf();
	return (0);
}

void	test_00_ft_printf()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 00 - TESTING FT_PRINTF (PRINTF - PART 1)\e[0m\n");
	int	res_ft_00 = ft_printf("\n00 - ft_printf [c] Imprime un solo carácter: [%c]", 'A');
	int	res_bc_00 = printf("\n00 - printf    [c] Imprime un solo carácter: [%c]", 'A');
	printf("\n");
	int	res_ft_01 = ft_printf("\n01 - ft_printf [s] Imprime una cadena de caracteres: [%s]", "Hola mundo!");
	int	res_bc_01 = printf("\n01 - printf    [s] Imprime una cadena de caracteres: [%s]", "Hola mundo!");
	printf("\n");
	int	res_ft_02 = ft_printf("\n02 - ft_printf [p] Un puntero en hexadecimal: [%p]", &res_bc_00);
	int	res_bc_02 = printf("\n02 - printf    [p] Un puntero en hexadecimal: [%p]", &res_bc_00);
	printf("\n");
	int	res_ft_03 = ft_printf("\n03 - ft_printf [d] Un número decimal (base 10): [%d]", -2024);
	int	res_bc_03 = printf("\n03 - printf    [d] Un número decimal (base 10): [%d]", -2024);
	printf("\n");
	int	res_ft_04 = ft_printf("\n04 - ft_printf [i] Imprime un entero en base 10: [%i]", -23478);
	int	res_bc_04 = printf("\n04 - printf    [i] Imprime un entero en base 10: [%i]", -23478);
	printf("\n");
	int	res_ft_05 = ft_printf("\n05 - ft_printf [u] Imprime un número decimal (base 10) sin signo: [%u]", -23478);
	int	res_bc_05 = printf("\n05 - printf    [u] Imprime un número decimal (base 10) sin signo: [%u]", -23478);
	printf("\n");
	int	res_ft_06 = ft_printf("\n06 - ft_printf [x] Imprime un número hexadecimal (base 16) en minúsculas: [%x]", 872634);
	int	res_bc_06 = printf("\n06 - printf    [x] Imprime un número hexadecimal (base 16) en minúsculas: [%x]", 872634);
	printf("\n");
	int	res_ft_07 = ft_printf("\n07 - ft_printf [X] Imprime un número hexadecimal (base 16) en mayúsculas: [%X]", 872634);
	int	res_bc_07 = printf("\n07 - printf    [X] Imprime un número hexadecimal (base 16) en mayúsculas: [%X]", 872634);
	printf("\n");
	int	res_ft_08 = ft_printf("\n08 - ft_printf [%%] para imprimir el símbolo del porcentaje: %%");
	int	res_bc_08 = printf("\n08 - printf    [%%] para imprimir el símbolo del porcentaje: %%");
	printf("\n");
	int	res_ft_09 = ft_printf("\n09 - ft_printf [s] Cadena NULL: %s", "NULL");
	int	res_bc_09 = printf("\n09 - printf    [s] Cadena NULL: %s", "NULL");
	printf("\n");
	int	res_ft_10 = ft_printf("\n10 - ft_printf [z] No existe: s");
	int	res_bc_10 = printf("\n10 - printf    [z] No existe: s");
	printf("\n");
	int	res_ft_11 = ft_printf("\n11 - ft_printf Múltimples argumentos: %c, %s, %p", 'R', "Hello word!", &res_ft_06);
	int	res_bc_11 = printf("\n11 - printf    Múltimples argumentos: %c, %s, %p", 'R', "Hello word!", &res_ft_06);
	printf("\n");
	int	res_ft_12 = ft_printf("\n12 - ft_printf Múltimples argumentos: %d, %d, %d, %i, %u", 365, 2147483647, -7483648, 0, -3450);
	int	res_bc_12 = printf("\n12 - printf    Múltimples argumentos: %d, %d, %d, %i, %u", 365, 2147483647, -7483648, 0, -3450);
	printf("\n");
	int	res_ft_13 = ft_printf("\n13 - ft_printf Múltimples argumentos: %x, %x, %X, %x, %x, %x", 0, 125, 255, -3456, 1, 10);
	int	res_bc_13 = printf("\n13 - printf    Múltimples argumentos: %x, %x, %X, %x, %x, %x", 0, 125, 255, -3456, 1, 10);
	printf("\n");

	printf("\n\n\t\t\tLEN DEVUELTOS:\n");
	printf("\n00 - [c] %s 		[%d]	<->	[%d]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n01 - [s] %s 		[%d]	<->	[%d]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n02 - [p] %s 		[%d]	<->	[%d]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n03 - [d] %s 		[%d]	<->	[%d]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n04 - [i] %s 		[%d]	<->	[%d]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n05 - [u] %s 		[%d]	<->	[%d]", (res_ft_05 == res_bc_05)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_05, res_bc_05);
	printf("\n06 - [x] %s 		[%d]	<->	[%d]", (res_ft_06 == res_bc_06)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_06, res_bc_06);
	printf("\n07 - [X] %s 		[%d]	<->	[%d]", (res_ft_07 == res_bc_07)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_07, res_bc_07);
	printf("\n08 - [mod] %s 	[%d]	<->	[%d]", (res_ft_08 == res_bc_08)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_08, res_bc_08);
	printf("\n09 - [s]=null %s	[%d]	<->	[%d]", (res_ft_09 == res_bc_09)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_09, res_bc_09);
	printf("\n10 - [z] %s		[%d]	<->	[%d]", (res_ft_10 == res_bc_10)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_10, res_bc_10);
	printf("\n11 - [ ] %s		[%d]	<->	[%d]", (res_ft_11 == res_bc_11)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_11, res_bc_11);
	printf("\n12 - [ ] %s		[%d]	<->	[%d]", (res_ft_12 == res_bc_12)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_12, res_bc_12);
	printf("\n13 - [ ] %s		[%d]	<->	[%d]", (res_ft_13 == res_bc_13)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_13, res_bc_13);
	printf("\n\n _________________________________________________________________\n");

	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@00 - TESTING FT_PRINTF (PACO)\e[0m\n");
	int	res_ft_14 = ft_printf("\n14 - ft_printf x=-1: %x", -1);
	int	res_bc_14 = printf("\n14 - printf    x=-1: %x", -1);
	printf("\n");
	int	res_ft_15 = ft_printf("\n15 - ft_printf x = 1: %x", 1);
	int	res_bc_15 = printf("\n15 - printf    x = 1: %x", 1);
	printf("\n");
	int	res_ft_16 = ft_printf("\n16 - ft_printf x = 99: %x", 99);
	int	res_bc_16 = printf("\n16 - printf    x = 99: %x", 99);
	printf("\n");
	int	res_ft_17 = ft_printf("\n17 - ft_printf x = -10: %x", -10);
	int	res_bc_17 = printf("\n17 - printf    x = -10: %x", -10);
	printf("\n");
	int	res_ft_18 = ft_printf("\n18 - ft_printf p = \"\": %p", "");
	int	res_bc_18 = printf("\n18 - printf    p = \"\": %p", "");
	printf("\n");
	int	res_ft_19 = ft_printf("\n19 - ft_printf p = \"\": %p", "");
	int	res_bc_19 = printf("\n19 - printf    p = \"\": %p", "");
	printf("\n");
	int	res_ft_20 = ft_printf("\n20 - ft_printf p = \"\": %p %p", (void *)LONG_MIN, (void *)LONG_MAX);
	int	res_bc_20 = printf("\n20 - printf    p = \"\": %p %p", (void *)LONG_MIN, (void *)LONG_MAX);
	printf("\n");
	int	res_ft_21 = ft_printf("\n21 - ft_printf  p = \"\": %p %p", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	int	res_bc_21 = printf("\n21 - printf     p = \"\": %p %p", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	printf("\n");
	int	res_ft_22 = ft_printf("\n22 - ft_printf p = \"\": %p %p", (void *)0, (void *)0);
	int	res_bc_22 = printf("\n22 - printf    p = \"\": %p %p", (void *)0, (void *)0);
	printf("\n");
	int	res_ft_23 = ft_printf("\n23 - ft_printf", LONG_MAX, LONG_MIN, ULONG_MAX);
	int	res_bc_23 = printf("\n23 - printf   ");
	printf("\n");
	int	res_ft_24 = ft_printf("\n24 - ft_printf");
	int	res_bc_24 = printf("\n24 - printf   ");
	printf("\n");
	int	res_ft_25 = ft_printf(" ");
	int	res_bc_25 = printf(" ");
	printf("\n");

	printf("\n\n\t\t\tLEN DEVUELTOS:");
	printf("\n\n\t\t\tFT_PRINTFT	PRINTF\n");
	printf("\n14 - [ ] %s		[%d]	<->	[%d]", (res_ft_14 == res_bc_14)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_14, res_bc_14);
	printf("\n15 - [ ] %s		[%d]	<->	[%d]", (res_ft_15 == res_bc_15)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_15, res_bc_15);
	printf("\n16 - [ ] %s		[%d]	<->	[%d]", (res_ft_16 == res_bc_16)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_16, res_bc_16);
	printf("\n17 - [ ] %s		[%d]	<->	[%d]", (res_ft_17 == res_bc_17)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_17, res_bc_17);
	printf("\n18 - [ ] %s		[%d]	<->	[%d]", (res_ft_18 == res_bc_18)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_18, res_bc_18);
	printf("\n19 - [ ] %s		[%d]	<->	[%d]", (res_ft_19 == res_bc_19)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_19, res_bc_19);
	printf("\n20 - [ ] %s		[%d]	<->	[%d]", (res_ft_20 == res_bc_20)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_20, res_bc_20);
	printf("\n21 - [ ] %s		[%d]	<->	[%d]", (res_ft_21 == res_bc_21)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_21, res_bc_21);
	printf("\n22 - [ ] %s		[%d]	<->	[%d]", (res_ft_22 == res_bc_22)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_22, res_bc_22);
	printf("\n23 - [ ] %s		[%d]	<->	[%d]", (res_ft_23 == res_bc_23)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_23, res_bc_23);
	printf("\n24 - [ ] %s		[%d]	<->	[%d]", (res_ft_24 == res_bc_24)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_24, res_bc_24);
	printf("\n25 - [ ] %s		[%d]	<->	[%d]", (res_ft_25 == res_bc_25)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_25, res_bc_25);

	printf("\n\n _________________________________________________________________\n");
	int	res_ft_26 = ft_printf("\n26[%r]", "");
	int	res_bc_26 = printf("\n26[%s]", "");
	printf("\n");
	int	res_ft_27 = ft_printf("\n27 - ft_printf (\001\002\007\v\010\f\r\n)");
	int	res_bc_27 = printf("\n27 - printf    (\001\002\007\v\010\f\r\n)");
	printf("\n");
	/*int	res_ft_28 = ft_printf("\n28 - ft_printf   %x %x %lx %lx %lx %x %x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	int	res_bc_28 = printf("\n28 - printf      %x %x %lx %lx %lx %x %x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\n");*/
	int	res_ft_29 = ft_printf("\n29 - ft_printf  %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	int	res_bc_29 = printf("\n29 - printf     %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	printf("\n");

	printf("\n\n\t\t\tLEN DEVUELTOS:");
	printf("\n\n\t\t\tFT_PRINTFT	PRINTF\n");
	printf("\n26 - [ ] %s		[%d]	<->	[%d]", (res_ft_26 == res_bc_26)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_26, res_bc_26);
	printf("\n27 - [ ] %s		[%d]	<->	[%d]", (res_ft_27 == res_bc_27)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_27, res_bc_27);
	// printf("\n28 - [ ] %s		[%d]	<->	[%d]", (res_ft_28 == res_bc_28)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_28, res_bc_28);
	printf("\n29 - [ ] %s		[%d]	<->	[%d]", (res_ft_29 == res_bc_29)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_29, res_bc_29);

	printf("\n\n _________________________________________________________________\n");
	int	res_ft_30 = ft_printf("\n30 - ft_printf E}<,#O~mI%x QHu^%i%phTD;%s\tL", -1605243987, 1947265344, (void *)-610900762724187360, ";E'Np\r\fcj");
	int	res_bc_30 = printf("\n30 - printf    E}<,#O~mI%x QHu^%i%phTD;%s\tL", -1605243987, 1947265344, (void *)-610900762724187360, ";E'Np\r\fcj");
	printf("\n");
	int	res_ft_31 = ft_printf("\n31 - ft_printf *V$~KX%i%iZwt0%ct^7$d\v%pj(68%c?z\vqEXXnT%cwrHwJ2?F,@%s\fu(^\rf%d)/J0%x[GB5<[o", -268175887, 446691849, -1288708047, (void *)-2241690766642785791, 1854289552, 129006195, "PAd#\\$V\tW\r^quM@VV\vP6Bp!i#.$:KwU-U2<&#ahF0\tHdx~F/", -1426432599, 991774531);
	int	res_bc_31 = printf("\n31 - printf    *V$~KX%i%iZwt0%ct^7$d\v%pj(68%c?z\vqEXXnT%cwrHwJ2?F,@%s\fu(^\rf%d)/J0%x[GB5<[o", -268175887, 446691849, -1288708047, (void *)-2241690766642785791, 1854289552, 129006195, "PAd#\\$V\tW\r^quM@VV\vP6Bp!i#.$:KwU-U2<&#ahF0\tHdx~F/", -1426432599, 991774531);
	printf("\n");
	int	res_ft_32 = ft_printf("\n32 - ft_printf   L\nkU%io#5?>bD]gr%sV9\rvh8j33&%d\rJf8u%cth&AG_!i7%sUIQRtZ%x\r[9}%%^}%Xn[H\f%XFhY\n%d[K!I= n>ko", 1387710263, "9B\"du%*", -1130677662, 642115986, "ZR4\\\t$\v41pkxYMRo8'>nCn$vDW\v)\n0\"<MDU)sN\f}`%d~K\"\r<k~8S", 1725409650, -786765451, -1242747062, 1831791912);
	int	res_bc_32 = printf("\n32 - printf      L\nkU%io#5?>bD]gr%sV9\rvh8j33&%d\rJf8u%cth&AG_!i7%sUIQRtZ%x\r[9}%%^}%Xn[H\f%XFhY\n%d[K!I= n>ko", 1387710263, "9B\"du%*", -1130677662, 642115986, "ZR4\\\t$\v41pkxYMRo8'>nCn$vDW\v)\n0\"<MDU)sN\f}`%d~K\"\r<k~8S", 1725409650, -786765451, -1242747062, 1831791912);
	printf("\n");
	int	res_ft_33 = ft_printf("\n33 - ft_printf  0TOVq%iEzH>KeM%c}.W\f%X(2mAR7\n]%%`I14%%%s%pW0Y~)=Q%X1a7K98&", -457678417, 1857647526, 2019843323, "0ba-Z}8V#`=x#(\nOKvTD%VxYjWWik\f(D/1I2N3A;O;e/(7jC1qkY_$W<@|&DR", (void *)-8733475495126666910, 1146725420);
	int	res_bc_33 = printf("\n33 - printf     0TOVq%iEzH>KeM%c}.W\f%X(2mAR7\n]%%`I14%%%s%pW0Y~)=Q%X1a7K98&", -457678417, 1857647526, 2019843323, "0ba-Z}8V#`=x#(\nOKvTD%VxYjWWik\f(D/1I2N3A;O;e/(7jC1qkY_$W<@|&DR", (void *)-8733475495126666910, 1146725420);
	printf("\n");
	int	res_ft_34 = ft_printf("\n34 - ft_printf %d%dd%d", 1, 2, -3);
	int	res_bc_34 = printf("\n34 - printf    %d%dd%d", 1, 2, -3);
	printf("\n");
	printf("\n");
	int	res_ft_35 = ft_printf("35 - [%s{Kh4(`X%xWk j&kxA%iU2VNCN", "7z\\}^\tsX:\t.Y8#YD~!s\nOFT&{E]", -668161753, -1897271339);
	printf("\n");
	int	res_bc_35 = printf("35 - [%s{Kh4(`X%xWk j&kxA%iU2VNCN", "7z\\}^\tsX:\t.Y8#YD~!s\nOFT&{E]", -668161753, -1897271339);
	printf("\n");
	int	res_ft_36 = ft_printf("\n%p", "");
	int	res_bc_36 = printf("\n%p", "");
	printf("\n");


	printf("\n\n\t\t\tLEN DEVUELTOS:");
	printf("\n\n\t\t\tFT_PRINTFT	PRINTF\n");
	printf("\n30 - [ ] %s		[%d]	<->	[%d]", (res_ft_30 == res_bc_30)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_30, res_bc_30);
	printf("\n31 - [ ] %s		[%d]	<->	[%d]", (res_ft_31 == res_bc_31)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_31, res_bc_31);
	printf("\n32 - [ ] %s		[%d]	<->	[%d]", (res_ft_32 == res_bc_32)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_32, res_bc_32);
	printf("\n33 - [ ] %s		[%d]	<->	[%d]", (res_ft_33 == res_bc_33)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_33, res_bc_33);
	printf("\n34 - [ ] %s		[%d]	<->	[%d]", (res_ft_34 == res_bc_34)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_34, res_bc_34);
	printf("\n35 - [ ] %s		[%d]	<->	[%d]", (res_ft_35 == res_bc_35)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_35, res_bc_35);
	printf("\n36 - [ ] %s		[%d]	<->	[%d]", (res_ft_36 == res_bc_36)?"\e[32mGOOD\e[0m":"\e\[31mERROR\e[0m", res_ft_36, res_bc_36);
	printf("\n\n _________________________________________________________________\n");
}
