/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:54:31 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 19:28:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libft.h"

/*	LIBC	*/
void	test_00_ft_isalpha();
void	test_01_ft_isdigit();
void	test_02_ft_isalnum();
void	test_03_ft_isascii();
void	test_04_ft_isprint();
void	test_05_ft_strlen();
void	test_06_ft_memset();
void	test_07_ft_bzero();
void	test_08_ft_memcpy();
void	test_09_ft_memmove();
void	test_10_ft_strlcpy();
void	test_11_ft_strlcat();
void	test_12_ft_toupper();
void	test_13_ft_tolower();
void	test_14_ft_strchr();
void	test_15_ft_strrchr();
void	test_16_ft_strncmp();
void	test_17_ft_memchr();
void	test_18_ft_memcmp();
void	test_19_ft_strnstr();
void	test_20_ft_atoi();
void	test_21_ft_calloc();
void	test_22_ft_strdup();
/*	ADDITIONAL - PART 2	*/
void	test_23_ft_substr();
void	test_24_ft_strjoin();
void	test_25_ft_strtrim();
void	test_26_ft_split();
void	test_27_ft_itoa();
void	test_28_ft_strmapi();
void	test_29_ft_striteri();
void	test_30_ft_putchar_fd();
void	test_31_ft_putstr_fd();
void	test_32_ft_putendl_fd();
void	test_33_ft_putnbr_fd();
/*	BONUS	*/
void	test_34_ft_lstnew();
void	test_35_ft_lstadd_front();
void	test_36_ft_lstsize();
void	test_37_ft_lstlast();
void	test_38_ft_lstadd_back();
void	test_39_ft_lstdelone();
void	test_40_ft_lstclear();
void	test_41_ft_lstiter();
void	test_42_ft_lstmap();
void	tester_all();

/* AUXILIARY */
static void	show_array(char **arr);
static char	ft_map_00(unsigned int i, char c);
static char	ft_map_01(unsigned int i, char c);
static void	ft_map_02(unsigned int i, char *c);
static void	ft_map_03(unsigned int i, char *c);
static void	lst_show(void *content);
static void lst_del(void *content);

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{	char *arg = argv[1];
		//printf("\e[1;1H\e[2J");
		printf("\n OPTION SELECTED: %s", arg);
		if (strcmp(arg, "0") == 0 || strcmp(arg, "isalpha") == 0)	 		{ test_00_ft_isalpha(); }
		else if (strcmp(arg, "1") == 0 || strcmp(arg, "isdigit") == 0)	 	{ test_01_ft_isdigit(); }
		else if (strcmp(arg, "2") == 0 || strcmp(arg, "isalnum") == 0)	 	{ test_02_ft_isalnum(); }
		else if (strcmp(arg, "3") == 0 || strcmp(arg, "isascii") == 0)	 	{ test_03_ft_isascii(); }
		else if (strcmp(arg, "4") == 0 || strcmp(arg, "isprint") == 0)	 	{ test_04_ft_isprint(); }
		else if (strcmp(arg, "5") == 0 || strcmp(arg, "strlen") == 0)	 	{ test_05_ft_strlen(); }
		else if (strcmp(arg, "6") == 0 || strcmp(arg, "memset") == 0)	 	{ test_06_ft_memset(); }
		else if (strcmp(arg, "7") == 0 || strcmp(arg, "bzero") == 0)	 	{ test_07_ft_bzero(); }
		else if (strcmp(arg, "8") == 0 || strcmp(arg, "memcpy") == 0)	 	{ test_08_ft_memcpy(); }
		else if (strcmp(arg, "9") == 0 || strcmp(arg, "memmove") == 0)	 	{ test_09_ft_memmove(); }
		else if (strcmp(arg, "10") == 0 || strcmp(arg, "strlcpy") == 0)	 	{ test_10_ft_strlcpy(); }
		else if (strcmp(arg, "11") == 0 || strcmp(arg, "strlcat") == 0)	 	{ test_11_ft_strlcat(); }
		else if (strcmp(arg, "12") == 0 || strcmp(arg, "toupper") == 0)	 	{ test_12_ft_toupper(); }
		else if (strcmp(arg, "13") == 0 || strcmp(arg, "tolower") == 0)	 	{ test_13_ft_tolower(); }
		else if (strcmp(arg, "14") == 0 || strcmp(arg, "strchr") == 0)	 	{ test_14_ft_strchr(); }
		else if (strcmp(arg, "15") == 0 || strcmp(arg, "strrchr") == 0)	 	{ test_15_ft_strrchr(); }
		else if (strcmp(arg, "16") == 0 || strcmp(arg, "strncmp") == 0)	 	{ test_16_ft_strncmp(); }
		else if (strcmp(arg, "17") == 0 || strcmp(arg, "memchr") == 0)	 	{ test_17_ft_memchr(); }
		else if (strcmp(arg, "18") == 0 || strcmp(arg, "memcmp") == 0)	 	{ test_18_ft_memcmp(); }
		else if (strcmp(arg, "19") == 0 || strcmp(arg, "strnstr") == 0)	 	{ test_19_ft_strnstr(); }
		else if (strcmp(arg, "20") == 0 || strcmp(arg, "atoi") == 0)	 	{ test_20_ft_atoi(); }
		else if (strcmp(arg, "21") == 0 || strcmp(arg, "calloc") == 0)	 	{ test_21_ft_calloc(); }
		else if (strcmp(arg, "22") == 0 || strcmp(arg, "strdup") == 0)	 	{ test_22_ft_strdup(); }
		else if (strcmp(arg, "23") == 0 || strcmp(arg, "substr") == 0)	 	{ test_23_ft_substr(); }
		else if (strcmp(arg, "24") == 0 || strcmp(arg, "strjoin") == 0)	 	{ test_24_ft_strjoin(); }
		else if (strcmp(arg, "25") == 0 || strcmp(arg, "strtrim") == 0)	 	{ test_25_ft_strtrim(); }
		else if (strcmp(arg, "26") == 0 || strcmp(arg, "split") == 0)	 	{ test_26_ft_split(); }
		else if (strcmp(arg, "27") == 0 || strcmp(arg, "itoa") == 0)	 	{ test_27_ft_itoa(); }
		else if (strcmp(arg, "28") == 0 || strcmp(arg, "strmapi") == 0)	 	{ test_28_ft_strmapi(); }
		else if (strcmp(arg, "29") == 0 || strcmp(arg, "striteri") == 0)	{ test_29_ft_striteri(); }
		else if (strcmp(arg, "30") == 0 || strcmp(arg, "putchar_fd") == 0)	{ test_30_ft_putchar_fd(); }
		else if (strcmp(arg, "31") == 0 || strcmp(arg, "putstr_fd") == 0)	{ test_31_ft_putstr_fd(); }
		else if (strcmp(arg, "32") == 0 || strcmp(arg, "putendl_fd") == 0)	{ test_32_ft_putendl_fd(); }
		else if (strcmp(arg, "33") == 0 || strcmp(arg, "putnbr_fd") == 0)	{ test_33_ft_putnbr_fd(); }
		else if (strcmp(arg, "34") == 0 || strcmp(arg, "lstnew") == 0)	 	{ test_34_ft_lstnew(); }
		else if (strcmp(arg, "35") == 0 || strcmp(arg, "lstadd_front") == 0)	{ test_35_ft_lstadd_front(); }
		else if (strcmp(arg, "36") == 0 || strcmp(arg, "lstsize") == 0)	 	{ test_36_ft_lstsize(); }
		else if (strcmp(arg, "37") == 0 || strcmp(arg, "lstlast") == 0)	 	{ test_37_ft_lstlast(); }
		else if (strcmp(arg, "38") == 0 || strcmp(arg, "lstadd_back") == 0)	{ test_38_ft_lstadd_back(); }
		else if (strcmp(arg, "39") == 0 || strcmp(arg, "lstdelone") == 0)	 	{ test_39_ft_lstdelone(); }
		else if (strcmp(arg, "40") == 0 || strcmp(arg, "lstclear") == 0)	 	{ test_40_ft_lstclear(); }
		else if (strcmp(arg, "41") == 0 || strcmp(arg, "lstiter") == 0)	 	{ test_41_ft_lstiter(); }
		else if (strcmp(arg, "42") == 0 || strcmp(arg, "lstmap") == 0)	 	{ test_42_ft_lstmap(); }
		else if (strcmp(arg, "99") == 0 || strcmp(arg, "all") == 0)	 		{ tester_all(); }
		else { printf("¡ ERROR : FUNCTION \"%s\" NOT FOUND!\n", arg); }
	}
	return (0);
}

void	test_00_ft_isalpha()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@00 - TESTING FT_ISALPHA (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_isalpha('a');
	int	res_bc_00 = isalpha('a');
	int	res_ft_01 = ft_isalpha('1');
	int	res_bc_01 = isalpha('1');
	int	res_ft_02 = ft_isalpha(' ');
	int	res_bc_02 = isalpha(' ');
	int	res_ft_03 = ft_isalpha('A');
	int	res_bc_03 = isalpha('A');
	int	res_ft_04 = ft_isalpha(37);
	int	res_bc_04 = isalpha(37);
	printf("\n ft_isalpha('a')	<->	isalpha('a')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 <= res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_isalpha('1')	<->	isalpha('1')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 <= res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_isalpha(' ')	<->	isalpha(' ')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 <= res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_isalpha('A')	<->	isalpha('A')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 <= res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_isalpha(37)		<->	isalpha(37)\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 <= res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_01_ft_isdigit()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@01 - TESTING FT_ISDIGIT (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_isdigit('0');
	int	res_bc_00 = isdigit('0');
	int	res_ft_01 = ft_isdigit('a');
	int	res_bc_01 = isdigit('a');
	int	res_ft_02 = ft_isdigit(' ');
	int	res_bc_02 = isdigit(' ');
	int	res_ft_03 = ft_isdigit('9');
	int	res_bc_03 = isdigit('9');
	int	res_ft_04 = ft_isdigit(37);
	int	res_bc_04 = isdigit(37);
	printf("\n ft_isdigit('0')	<->	isdigit('0')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 <= res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_isdigit('a')	<->	isdigit('a')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 <= res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_isdigit(' ')	<->	isdigit(' ')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 <= res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_isdigit('9')	<->	isdigit('9')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 <= res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_isdigit(37)		<->	isdigit(37)\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 <= res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_02_ft_isalnum()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@02 - TESTING FT_ISALNUM (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_isalnum('0');
	int	res_bc_00 = isalnum('0');
	int	res_ft_01 = ft_isalnum('a');
	int	res_bc_01 = isalnum('a');
	int	res_ft_02 = ft_isalnum(' ');
	int	res_bc_02 = isalnum(' ');
	int	res_ft_03 = ft_isalnum('B');
	int	res_bc_03 = isalnum('B');
	int	res_ft_04 = ft_isalnum(37);
	int	res_bc_04 = isalnum(37);
	printf("\n ft_isalnum('0')	<->	isalnum('0')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 <= res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_isalnum('a')	<->	isalnum('a')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 <= res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_isalnum(' ')	<->	isalnum(' ')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 <= res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_isalnum('B')	<->	isalnum('B')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 <= res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_isalnum(37)		<->	isalnum(37)\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 <= res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_03_ft_isascii()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@03 - TESTING FT_ISASCII (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_isascii('0');
	int	res_bc_00 = isascii('0');
	int	res_ft_01 = ft_isascii('^');
	int	res_bc_01 = isascii('^');
	int	res_ft_02 = ft_isascii('-');
	int	res_bc_02 = isascii('-');
	int	res_ft_03 = ft_isascii('\n');
	int	res_bc_03 = isascii('\n');
	int	res_ft_04 = ft_isascii(37);
	int	res_bc_04 = isascii(37);
	printf("\n ft_isascii('0')	<->	isascii('0')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_isascii('^')	<->	isascii('^')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_isascii('-')	<->	isascii('-')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_isascii('\\n')	<->	isascii('\\n')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_isascii(37)		<->	isascii(37)\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_04_ft_isprint()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@04 - TESTING FT_ISPRINT (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_isprint('0');
	int	res_bc_00 = isprint('0');
	int	res_ft_01 = ft_isprint('^');
	int	res_bc_01 = isprint('^');
	int	res_ft_02 = ft_isprint(' ');
	int	res_bc_02 = isprint(' ');
	int	res_ft_03 = ft_isprint('\n');
	int	res_bc_03 = isprint('\n');
	int	res_ft_04 = ft_isprint(37);
	int	res_bc_04 = isprint(37);
	printf("\n ft_isprint('0')	<->	isprint('0')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 <= res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_isprint('^')	<->	isprint('^')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 <= res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_isprint(' ')	<->	isprint(' ')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 <= res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_isprint('\\n')	<->	isprint('\\n')\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 <= res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_isprint(37)		<->	isprint(37)\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 <= res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_05_ft_strlen()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@05 - TESTING FT_STRLEN (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_strlen("hello");
	int	res_bc_00 = strlen("hello");
	int	res_ft_01 = ft_strlen("^");
	int	res_bc_01 = strlen("^");
	int	res_ft_02 = ft_strlen(" ");
	int	res_bc_02 = strlen(" ");
	int	res_ft_03 = ft_strlen("\n");
	int	res_bc_03 = strlen("\n");
	int	res_ft_04 = ft_strlen("");
	int	res_bc_04 = strlen("");
	printf("\n ft_strlen(\"hello\")	<->	strlen(\"hello\")\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strlen(\"^\")		<->	strlen(\"^\")\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strlen(\" \")		<->	strlen(\" \")\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_strlen(\"\\n\")	<->	strlen(\"\\n\")\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_strlen(\"\")		<->	strlen(\"\")\n");
	printf("%s 		[%d]	<->	[%d]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n _________________________________________________________________");
}

void	test_06_ft_memset()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@06 - TESTING FT_MEMSET (LIBC - PART 1)\e[0m\n");

	char str_00[] = "hello";
	char *res_ft_00 = ft_memset(&str_00, '*', 2);
	char str_01[] = "hello";
	char *res_bc_00 = memset(&str_01, '*', 2);
	char str_02[] = "fill this";
	char *res_ft_01 = ft_memset(&str_02, '_', 4);
	char str_03[] = "fill this";
	char *res_bc_01 = memset(&str_03, '_', 4);
	char str_04[] = " ";
	char *res_ft_02 = ft_memset(&str_04, 'a', 1);
	char str_05[] = " ";
	char *res_bc_02 = memset(&str_05, 'a', 1);
	char str_06[] = "what is this";
	char *res_ft_03 = ft_memset(&str_06, 37, 1);
	char str_07[] = "what is this";
	char *res_bc_03 = memset(&str_07, 37, 1);
	char str_08[] = "proof";
	char *res_ft_04 = ft_memset(&str_08, ' ', 1);
	char str_09[] = "proof";
	char *res_bc_04 = memset(&str_09, ' ', 1);
	printf("\n ft_memset(\"hello\", '*', 2)		<->	memset(\"hello\", '*', 2)\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_memset(\"fill this\", '_', 4)		<->	memset(\"fill this\", '_', 4)\n");
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_memset(" ", 'a', 1)			<->	memset(" ", 'a', 1)\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_02, res_bc_02) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_memset(\"what is this?\", 37, 1)	<->	memset(\"what is this?\", 37, 1)\n");
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_03, res_bc_03) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_memset(\"proof\", ' ', 1)		<->	memset(\"proof\", ' ', 1)\n");
	printf("%s [%s]				<->	[%s]", (strcmp(res_ft_04, res_bc_04) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_07_ft_bzero()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@07 - TESTING FT_BZERO (LIBC - PART 1)\e[0m\n");
	char res_ft_00[] = "hello";
	ft_bzero(res_ft_00, 2);
	char res_bc_00[] = "hello";
	bzero(res_bc_00, 2);
	printf("\n ft_bzero(\"hello\", 2)	<->	bzero(\"hello\", 2)\n");
	printf("%s [%s] 		<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n\n _________________________________________________________________");
}

void	test_08_ft_memcpy()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@08 - TESTING FT_MEMCPY (LIBC - PART 1)\e[0m\n");
	char res_ft_00[] = "This is a proof";
	ft_memcpy(res_ft_00, "copy this", 4);
	char res_bc_00[] = "This is a proof";
	memcpy(res_bc_00, "copy this", 4);
	char res_ft_01[] = "This";
	ft_memcpy(res_ft_01, "copy this", 2);
	char res_bc_01[] = "This";
	memcpy(res_bc_01, "copy this", 2);
	printf("\n ft_memcpy(\"This is a proof\", \"copy this\", 4)	<->	memcpy(\"This is a proof\", \"copy this\", 4)\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_memcpy(\"This\", \"copy this\", 2)		<->	memcpy(\"This\", \"copy this\", 2)\n");
	printf("%s [%s] 					<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n\n _________________________________________________________________");
}

void	test_09_ft_memmove()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@09 - TESTING FT_MEMMOVE (LIBC - PART 1)\e[0m\n");
	char res_ft_00[] = "This is a proof";
	ft_memmove(res_ft_00, "copy this", 4);
	char res_bc_00[] = "This is a proof";
	memmove(res_bc_00, "copy this", 4);
	char res_ft_01[] = "This";
	ft_memmove(res_ft_01, "copy this", 2);
	char res_bc_01[] = "This";
	memmove(res_bc_01, "copy this", 2);
	printf("\n ft_memmove(\"This is a proof\", \"copy this\", 4)	<->	memmove(\"This is a proof\", \"copy this\", 4)\n");
	printf("%s [%s]				<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_memmove(\"This\", \"copy this\", 2)		<->	memmove(\"This\", \"copy this\", 2)\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n\n _________________________________________________________________");
}

void	test_10_ft_strlcpy()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@10 - TESTING FT_STRLCPY (LIBC - PART 1)\e[0m\n");


	char res_ft_00[20] = {"--------------------"};
    const char *origen = "Hola, mundo!";
    ft_strlcpy(res_ft_00, origen, sizeof(res_ft_00));
	char res_ft_01[10] = {"----------"};
    const char *origen2 = "Cadena muy larga para el buffer";
    ft_strlcpy(res_ft_01, origen2, sizeof(res_ft_01));

	char res_bc_00[] = "Hola, mundo!";
	char res_bc_01[] = "Cadena mu";
	// strlcpy(res_bc_01, "copy this", 5);
	printf("\n ft_strlcpy(\"--------------------\", \"Hola, mundo!\", sizeof)	<->	strlcpy(\"--------------------\", \"Hola, mundo!\", sizeof)\n");
	printf("%s [%s] 					<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strlcpy(\"----------\", \"Cadena muy larga para el buffer\", sizeof)		<->	strlcpy(\"----------\", \"Cadena muy larga para el buffer\", sizeof)\n");
	printf("%s [%s] 					<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n\n _________________________________________________________________");
}

void	test_11_ft_strlcat()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@11 - TESTING FT_STRLCAT (LIBC - PART 1)\e[0m\n");


	char res_ft_00[30] = "Hola, ";
    const char *origen = "mundo!";
    ft_strlcat(res_ft_00, origen, sizeof(res_ft_00));
    char res_ft_01[12] = "Hola, ";
    const char *origen_01 = "mundo!";
    ft_strlcat(res_ft_01, origen_01, sizeof(res_ft_01));
	int size_01 = sizeof(res_ft_00);
	int size_02 = sizeof(res_ft_01);

	char res_bc_00[20] = "Hola, mundo!";
	char res_bc_01[20] = "Hola, mundo";

	printf("\n ft_strlcat(\"Hola, \", \"mundo!\", %d)	<->	strlcat(\"Hola, \", \"mundo!\", %d)\n", size_01, size_01);
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strlcat(\"Hola, \", \"mundo!\", %d)	<->	strlcat(\"Hola, \", \"mundo!\", %d)\n", size_02, size_02);
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n\n _________________________________________________________________");
}

void	test_12_ft_toupper()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@12 - TESTING FT_TOUPPER (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_toupper('0');
	int	res_bc_00 = toupper('0');
	int	res_ft_01 = ft_toupper('a');
	int	res_bc_01 = toupper('a');
	int	res_ft_02 = ft_toupper(' ');
	int	res_bc_02 = toupper(' ');
	int	res_ft_03 = ft_toupper('i');
	int	res_bc_03 = toupper('i');
	int	res_ft_04 = ft_toupper(37);
	int	res_bc_04 = toupper(37);
	printf("\n ft_toupper('0')	<->	toupper('0')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_toupper('a')	<->	toupper('a')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_toupper(' ')	<->	toupper(' ')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_toupper('i')	<->	toupper('i')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_toupper(37)		<->	toupper(37)\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_13_ft_tolower()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@13 - TESTING FT_TOLOWER (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_tolower('0');
	int	res_bc_00 = tolower('0');
	int	res_ft_01 = ft_tolower('a');
	int	res_bc_01 = tolower('a');
	int	res_ft_02 = ft_tolower('B');
	int	res_bc_02 = tolower('B');
	int	res_ft_03 = ft_tolower('I');
	int	res_bc_03 = tolower('I');
	int	res_ft_04 = ft_tolower(37);
	int	res_bc_04 = tolower(37);
	printf("\n ft_tolower('0')	<->	tolower('0')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_tolower('a')	<->	tolower('a')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_tolower('B')	<->	tolower('B')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_tolower('I')	<->	tolower('I')\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_tolower(37)		<->	tolower(37)\n");
	printf("%s [%c] 		<->	[%c]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_14_ft_strchr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@14 - TESTING FT_STRCHR (LIBC - PART 1)\e[0m\n");
	char	*res_ft_00 = ft_strchr("Find in this", '0');
	char	*res_bc_00 = strchr("Find in this", '0');
	char	*res_ft_01 = ft_strchr("F\0ind in this", 'i');
	char	*res_bc_01 = strchr("F\0ind in this", 'i');
	char	*res_ft_02 = ft_strchr("Find in this", ' ');
	char	*res_bc_02 = strchr("Find in this", ' ');
	char	*res_ft_03 = ft_strchr("Find in thIs", 'I');
	char	*res_bc_03 = strchr("Find in thIs", 'I');
	char	*res_ft_04 = ft_strchr("Find in this", 37);
	char	*res_bc_04 = strchr("Find in this", 37);
	printf("\n ft_strchr(\"Find in this\", '0')		<->	strchr(\"Find in this\", '0')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strchr(\"F\\0ind in this\", 'i')	<->	strchr(\"F\\0ind in this\", 'i')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strchr(\"Find in this\", ' ')		<->	strchr(\"Find in this\", ' ')\n");
	printf("%s [%s] 			<->	[%s]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_strchr(\"Find in thIs\", 'I')		<->	strchr(\"Find in thIs\", 'I')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_strchr(\"Find in this\", 37)		<->	strchr(\"Find in this\", 37)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_15_ft_strrchr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@15 - TESTING FT_STRRCHR (LIBC - PART 1)\e[0m\n");
	char	*res_ft_00 = ft_strrchr("Find in this", '0');
	char	*res_bc_00 = strrchr("Find in this", '0');
	char	*res_ft_01 = ft_strrchr("F\0ind in this", 'i');
	char	*res_bc_01 = strrchr("F\0ind in this", 'i');
	char	*res_ft_02 = ft_strrchr("Find in this", ' ');
	char	*res_bc_02 = strrchr("Find in this", ' ');
	char	*res_ft_03 = ft_strrchr("Find in thIs", 'I');
	char	*res_bc_03 = strrchr("Find in thIs", 'I');
	char	*res_ft_04 = ft_strrchr("Find in this", 37);
	char	*res_bc_04 = strrchr("Find in this", 37);
	printf("\n ft_strrchr(\"Find in this\", '0')	<->	strrchr(\"Find in this\", '0')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strrchr(\"F\\0ind in this\", 'i')	<->	strrchr(\"F\\0ind in this\", 'i')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strrchr(\"Find in this\", ' ')	<->	strrchr(\"Find in this\", ' ')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_strrchr(\"Find in thIs\", 'I')	<->	strrchr(\"Find in thIs\", 'I')\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_strrchr(\"Find in this\", 37)		<->	strrchr(\"Find in this\", 37)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_16_ft_strncmp()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@16 - TESTING FT_STRNCMP (LIBC - PART 1)\e[0m\n");
	int res_ft_00 = ft_strncmp("Is this equal?", "Is this equal?", 14);
	int res_bc_00 = strncmp("Is this equal?", "Is this equal?", 14);
	int res_ft_01 = ft_strncmp("Is this equal?", "Is this Lequal?", 4);
	int res_bc_01 = strncmp("Is this equal?", "Is this Lequal?", 4);
	int res_ft_02 = ft_strncmp("Is not this equal?", "Is this equal?", 14);
	int res_bc_02 = strncmp("Is not this equal?", "Is this equal?", 14);
	printf("\n ft_strncmp(\"Is this equal?\", \"Is this equal?\", 14)	<->	strncmp(\"Is this equal?\", \"Is this equal?\", 14)\n");
	printf("%s [%d] 						<->	[%d]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strncmp(\"Is this equal?\", \"Is this Lequal?\", 4)	<->	strncmp(\"Is this equal?\", \"Is this Lequal?\", 4)\n");
	printf("%s [%d] 						<->	[%d]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strncmp(\"Is not this equal?\", \"Is this equal?\", 14)	<->	strncmp(\"Is not this equal?\", \"Is this equal?\", 14)\n");
	printf("%s [%d] 						<->	[%d]", ((res_ft_02 * res_bc_02) >= 0 )?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n\n _________________________________________________________________");
}

void	test_17_ft_memchr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@17 - TESTING FT_MEMCHR (LIBC - PART 1)\e[0m\n");
	char	*res_ft_00 = ft_memchr("Find in this", '0', 5);
	char	*res_bc_00 = memchr("Find in this", '0', 5);
	char	*res_ft_01 = ft_memchr("Find in this", 'i', 5);
	char	*res_bc_01 = memchr("Find in this", 'i', 5);
	char	*res_ft_02 = ft_memchr("Find in this", ' ', 5);
	char	*res_bc_02 = memchr("Find in this", ' ', 5);
	char	*res_ft_03 = ft_memchr("Find in thIs", 'I', 5);
	char	*res_bc_03 = memchr("Find in thIs", 'I', 5);
	char	*res_ft_04 = ft_memchr("Find in this", 37, 5);
	char	*res_bc_04 = memchr("Find in this", 37, 5);
	printf("\n ft_memchr(\"Find in this\", '0', 5)	<->	memchr(\"Find in this\", '0', 5)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_memchr(\"Find in this\", 'i', 5)	<->	memchr(\"Find in this\", 'i', 5)\n");
	printf("%s [%s] 			<->	[%s]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_memchr(\"Find in this\", ' ', 5)	<->	memchr(\"Find in this\", ' ', 5)\n");
	printf("%s [%s] 			<->	[%s]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_memchr(\"Find in thIs\", 'I', 5)	<->	memchr(\"Find in thIs\", 'I', 5)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_memchr(\"Find in this\", 37, 5)	<->	memchr(\"Find in this\", 37, 5)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_18_ft_memcmp()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@18 - TESTING FT_MEMCMP (LIBC - PART 1)\e[0m\n");
	int res_ft_00 = ft_memcmp("Is this equal?", "Is this equal?", 14);
	int res_bc_00 = memcmp("Is this equal?", "Is this equal?", 14);
	int res_ft_01 = ft_memcmp("Is this equal?", "Is this Lequal?", 4);
	int res_bc_01 = memcmp("Is this equal?", "Is this Lequal?", 4);
	int res_ft_02 = ft_memcmp("Is not this equal?", "Is this equal?", 14);
	int res_bc_02 = memcmp("Is not this equal?", "Is this equal?", 14);
	printf("\n ft_memcmp(\"Is this equal?\", \"Is this equal?\", 14)	<->	memcmp(\"Is this equal?\", \"Is this equal?\", 14)\n");
	printf("%s [%d] 						<->	[%d]", (res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_memcmp(\"Is this equal?\", \"Is this Lequal?\", 4)	<->	memcmp(\"Is this equal?\", \"Is this Lequal?\", 4)\n");
	printf("%s [%d] 						<->	[%d]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_memcmp(\"Is not this equal?\", \"Is this equal?\", 14)	<->	memcmp(\"Is not this equal?\", \"Is this equal?\", 14)\n");
	printf("%s [%d] 						<->	[%d]", ((res_ft_02 * res_bc_02) >= 0 )?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n\n _________________________________________________________________");
}

void	test_19_ft_strnstr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@19 - TESTING FT_STRNSTR (LIBC - PART 1)\e[0m\n");

	char	*res_ft_00 = ft_strnstr("Is this equal?", "this", 14);
	char	*res_bc_00 = "this equal?";
	char	*res_ft_01 = ft_strnstr("Is this equal?", "this Lequ", 4);
	char	*res_bc_01 = NULL;
	char	*res_ft_02 = ft_strnstr("Is not this equal?", "not", 6);
	char	*res_bc_02 = "not this equal?";
	printf("\n ft_strnstr(\"Is this equal?\", \"this\", 14)	<->	strnstr(\"Is this equal?\", \"this\", 14)\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strnstr(\"Is this equal?\", \"this Lequ\", 4)	<->	strnstr(\"Is this equal?\", \"this Lequ\", 4)\n");
	printf("%s [%s] 					<->	[%s]", (res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strnstr(\"Is not this equal?\", \"not\", 6)	<->	strnstr(\"Is not this equal?\", \"not\", 6)\n");
	printf("%s [%s] 				<->	[%s]", (res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n\n _________________________________________________________________");
}

void	test_20_ft_atoi()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@20 - TESTING FT_ATOI (LIBC - PART 1)\e[0m\n");
	int	res_ft_00 = ft_atoi("12345");
	int	res_bc_00 = atoi("12345");
	int	res_ft_01 = ft_atoi("-4565");
	int	res_bc_01 = atoi("-4565");
	int	res_ft_02 = ft_atoi("  4 5");
	int	res_bc_02 = atoi("  4 5");
	int	res_ft_03 = ft_atoi("B");
	int	res_bc_03 = atoi("B");
	int	res_ft_04 = ft_atoi("++-++-234");
	int	res_bc_04 = atoi("++-++-234");
	printf("\n ft_atoi(\"12345\")	<->	atoi(\"12345\")\n");
	printf("%s [%d] 		<->	[%d]",(res_ft_00 == res_bc_00)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_atoi(\"-4565\")	<->	atoi(\"-4565\")\n");
	printf("%s [%d] 		<->	[%d]",(res_ft_01 == res_bc_01)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_atoi(\"  4 5\")	<->	atoi(\"  4 5\")\n");
	printf("%s 	[%d]		<->	[%d]",(res_ft_02 == res_bc_02)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_atoi(\"B\")		<->	atoi(\"B\")\n");
	printf("%s 	[%d]		<->	[%d]",(res_ft_03 == res_bc_03)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n ft_atoi(\"++-++-234\")	<->	atoi(\"++-++-234\")\n");
	printf("%s 	[%d]		<->	[%d]",(res_ft_04 == res_bc_04)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04, res_bc_04);
	printf("\n\n _________________________________________________________________");
}

void	test_21_ft_calloc()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@21 - TESTING FT_CALLOC (LIBC - PART 1)\e[0m\n");
	char	*res_ft_00 = ft_calloc(6, sizeof(char));
	char	*res_bc_00 = calloc(6, sizeof(char));
	// strlcpy(res_ft_00, "Hello", 6);
	// strcpy(res_bc_00, "Hello");
	printf("\n ft_calloc(6, sizeof(char))	<->	calloc(6, sizeof(char))\n");
	printf("%s [%s] 			<->	[%s]",  (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n\n _________________________________________________________________");
}

void	test_22_ft_strdup()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@22 - TESTING FT_STRDUP (LIBC - PART 1)\e[0m\n");
	char	*res_ft_00 = ft_strdup("First\0number");
	char	*res_bc_00 = strdup("First\0number");
	char	*res_ft_01 = ft_strdup("Pri\nmero");
	char	*res_bc_01 = strdup("Pri\nmero");
	char	*res_ft_02 = ft_strdup("");
	char	*res_bc_02 = strdup("");
	char	*res_ft_03 = ft_strdup("12345:");
	char	*res_bc_03 = strdup("12345:");
	printf("\n ft_strdup(\"First\\0number\")	<->	strdup(\"First\\0number\")\n");
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_00, res_bc_00) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, res_bc_00);
	printf("\n ft_strdup(\"Pri\\nmero\")		<->	strdup(\"Pri\\nmero\")\n");
	printf("%s [%s] 				<->	[%s]", (strcmp(res_ft_01, res_bc_01) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, res_bc_01);
	printf("\n ft_strdup(\"\")			<->	strdup(\"\")\n");
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_02, res_bc_02) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, res_bc_02);
	printf("\n ft_strdup(\"12345:\")		<->	strdup(\"12345:\")\n");
	printf("%s [%s] 			<->	[%s]", (strcmp(res_ft_03, res_bc_03) == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, res_bc_03);
	printf("\n\n _________________________________________________________________");
}

void	test_23_ft_substr()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@23 - TESTING FT_SUBSTR (ADDITIONAL - PART 2)\e[0m\n");
	char	str_00[] = "This is a proof";
	char	*res_ft_00 = ft_substr(str_00, 2, 5);
	char	str_01[] = "This is a proof";
	char	*res_ft_01 = ft_substr(str_01, 10, 7);
	char	str_02[] = "This is a proof";
	char	*res_ft_02 = ft_substr(str_02, 15, 1);
	char	str_03[] = "This is a proof";
	char	*res_ft_03 = ft_substr(str_03, 0, 9);
	printf("\n00 - ft_substr(\"%s\", 2, 5)\n", str_00);
	printf("00 - %s [%s] 			<->	[%s]", (strcmp(res_ft_00, "is is") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00, "is is");
	printf("\n01 - ft_substr(\"%s\", 10, 7)\n", str_01);
	printf("01 - %s [%s] 			<->	[%s]", (strcmp(res_ft_01, "proof") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01, "a proof");
	printf("\n02 - ft_substr(\"%s\", 15, 1)\n", str_02);
	printf("02 - %s [%s] 				<->	[%s]", (strcmp(res_ft_02, "") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02, "");
	printf("\n03 - ft_substr(\"%s\", 0, 9)\n", str_03);
	printf("03 - %s [%s] 			<->	[%s]", (strcmp(res_ft_03, "This is a") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03, "");
	printf("\n\n _________________________________________________________________");
}

void	test_24_ft_strjoin()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@24 - TESTING FT_STRJOIN (ADDITIONAL - PART 2)\e[0m\n");

	char	str_00[50] = "This is a string";
	char	str_01[50] = "*This*is*a*string*";
	char	str_02[50] = "This=is?a=prooofff=";
	char	str_03[50] = "This is a string";
	char	*res_ft_00 = ft_strjoin(str_00, "add this");
	char	*res_ft_01 = ft_strjoin(str_01, "not add this");
	char	*res_ft_02 = ft_strjoin(str_02, "add this.");
	char	*res_ft_03 = ft_strjoin(str_03, "add lol this");
	printf("\n ft_strjoin(\"This is a string\", \"add this\")\n");
	printf("%s strjoin		<->	[%s]", (strcmp(res_ft_00, "This is a stringadd this") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00);
	printf("\n ft_strjoin(\"*This*is*a*string*\", \"add this\")\n");
	printf("%s strjoin		<->	[%s]", (strcmp(res_ft_01, "*This*is*a*string*not add this") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01);
	printf("\n ft_strjoin(\"This=is?a=prooofff=\", \"add this\")\n");
	printf("%s strjoin		<->	[%s]", (strcmp(res_ft_02, "This=is?a=prooofff=add this.") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02);
	printf("\n ft_strjoin(\"This is a string\", \"add this\")\n");
	printf("%s strjoin		<->	[%s]", (strcmp(res_ft_03, "This is a stringadd lol this") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03);
	free(res_ft_00);
	free(res_ft_01);
	free(res_ft_02);
	free(res_ft_03);
	printf("\n\n _________________________________________________________________");
}

void	test_25_ft_strtrim()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@25 - TESTING FT_STRTRIM (ADDITIONAL - PART 2)\e[0m\n");
	char	*res_ft_00 = ft_strtrim("This is a string", "is");
	char	*res_ft_01 = ft_strtrim("*s*****This*is*a*stringssssss******", "*s");
	char	*res_ft_02 = ft_strtrim("  ===This=is?a=prooofff=", "(=)");
	char	*res_ft_03 = ft_strtrim("This is a string", "xcvb");
	printf("\n ft_strtrim(\"This is a string\", \"is\")\n");
	printf("%s strtrim		<->	[%s]", (strcmp(res_ft_00, "This is a string") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00);
	printf("\n ft_strtrim(\"*s*****This*is*a*stringssssss******\", \"*s\")\n");
	printf("%s strtrim		<->	[%s]", (strcmp(res_ft_01, "This*is*a*string") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01);
	printf("\n ft_strtrim(\"  ===This=is?a=prooofff=\", \"(=)\")\n");
	printf("%s strtrim		<->	[%s]", (strcmp(res_ft_02, "  ===This=is?a=prooofff") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02);
	printf("\n ft_strtrim(\"This is a string\", \"xcvb\")\n");
	printf("%s strtrim		<->	[%s]", (strcmp(res_ft_03, "This is a string") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03);
	printf("\n\n _________________________________________________________________");
}

void	test_26_ft_split()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@26 - TESTING FT_SPLIT (ADDITIONAL - PART 2)\e[0m\n");
	char str0[] = "This is a string";
	char	**res_ft_00 = ft_split(str0, ' ');
	char str1[] = "*This*is*a*string*";
	char	**res_ft_01 = ft_split(str1, '*');
	char str2[] = "This=is?a=prooofff=";
	char	**res_ft_02 = ft_split(str2, '?');
	char str3[] = "This is a string";
	char	**res_ft_03 = ft_split(str3, 'x');
	char str4[] = "hello!";
	char	**res_ft_04 = ft_split(str4, ' ');
	printf("\n ft_split(\"This is a string\", ' ')	<->	");
	show_array(res_ft_00);
	printf("\n ft_split(\"*This*is*a*string*\", '*')	<->	");
	show_array(res_ft_01);
	printf("\n ft_split(\"This=is?a=prooofff=\", '?')	<->	");
	show_array(res_ft_02);
	printf("\n ft_split(\"This is a string\", 'x')	<->	");
	show_array(res_ft_03);
	printf("\n ft_split(\"hello!\", ' ')		<->	");
	show_array(res_ft_04);
	printf("\n\n _________________________________________________________________");
}

void	test_27_ft_itoa()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@27 - TESTING FT_ITOA (ADDITIONAL - PART 2)\e[0m\n");
	char	*res_ft_00 = ft_itoa(24563);
	char	*res_ft_01 = ft_itoa(-5665);
	char	*res_ft_02 = ft_itoa(2147483647);
	char	*res_ft_03 = ft_itoa(-214748);
	char	*res_ft_04 = ft_itoa(0);
	printf("\n ft_itoa(24563)\n");
	printf("%s [%s]", (strcmp(res_ft_00, "24563") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00);
	printf("\n ft_itoa(-5665)\n");
	printf("%s [%s]", (strcmp(res_ft_01, "-5665") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01);
	printf("\n ft_itoa(2147483647)\n");
	printf("%s [%s]", (strcmp(res_ft_02, "2147483647") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_02);
	printf("\n ft_itoa(-214748)\n");
	printf("%s [%s]", (strcmp(res_ft_03, "-214748") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_03);
	printf("\n ft_itoa(0)\n");
	printf("%s [%s]", (strcmp(res_ft_04, "0") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_04);
	printf("\n\n _________________________________________________________________");
}

void	test_28_ft_strmapi()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@28 - TESTING FT_STRMAPI (ADDITIONAL - PART 2)\e[0m\n");
	char	*res_ft_00 = ft_strmapi("this is a string", &ft_map_00);
	char	*res_ft_01 = ft_strmapi("THIS IS A STRING", &ft_map_01);
	printf("\n ft_strmapi(\"this is a string\", ft_toupper)\n");
	printf("%s [%s]", (strcmp(res_ft_00, "THIS IS A STRING") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00);
	printf("\n ft_strmapi(\"THIS IS A STRING\", ft_tolower)\n");
	printf("%s [%s]", (strcmp(res_ft_01, "this is a string") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01);
	printf("\n\n _________________________________________________________________");
}

void	test_29_ft_striteri()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@29 - TESTING FT_STRITER (ADDITIONAL - PART 2)\e[0m\n");
	char	res_ft_00[] = "this is a string";
	ft_striteri(res_ft_00, &ft_map_02);
	char	res_ft_01[] = "this is a string";
	ft_striteri(res_ft_01, &ft_map_03);
	printf("\n ft_striteri(\"this is a string\", ft_toupper)\n");
	printf("%s [%s]", (strcmp(res_ft_00, "THIS IS A STRING") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_00);
	printf("\n ft_striteri(\"THIS IS A STRING\", ft_tolower)\n");
	printf("%s [%s]", (strcmp(res_ft_01, "this is a string") == 0)?"\e[32mGOOD\e[0m":"\e[31mERROR\e[0m", res_ft_01);
	printf("\n\n _________________________________________________________________");
}

void	test_30_ft_putchar_fd()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@30 - TESTING FT_PUTCHAR (ADDITIONAL - PART 2)\e[0m\n");
	printf("[32mGOOD\e[0m \nHello\n");
	ft_putchar_fd('H', 1);
	ft_putchar_fd('e', 1);
	ft_putchar_fd('l', 1);
	ft_putchar_fd('l', 1);
	ft_putchar_fd('o', 1);
	ft_putchar_fd('\n', 1);
	printf("\n\n _________________________________________________________________");
}

void	test_31_ft_putstr_fd()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@31 - TESTING FT_PUTSTR_ (ADDITIONAL - PART 2)\e[0m\n");
	printf("\e[32mGOOD\e[0m \nHello\n");
	ft_putstr_fd("Hello", 1);
	printf("\n\n _________________________________________________________________");
}

void	test_32_ft_putendl_fd()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@32 - TESTING FT_PUTENDL (ADDITIONAL - PART 2)\e[0m\n");
	printf("\e[32mGOOD\e[0m \nHello\n\n");
	ft_putendl_fd("Hello", 1);
	printf("\n\n _________________________________________________________________");
}

void	test_33_ft_putnbr_fd()
{
	int	len = 0;
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@33 - TESTING FT_PUTNBR_FD (ADDITIONAL - PART 2)\e[0m\n");
	printf("\e[32mGOOD\e[0m \n-987441]\n");
	len = ft_putnbr_fd(-987441, 1);
	printf("] len = %d", len);
	printf("\n\n _________________________________________________________________");
}

void	test_34_ft_lstnew()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@34 - TESTING FT_LSTNEW (BONUS)\e[0m\n");
	t_list *my_list;

	char array_str[7][20] = {"This", "is", "a", "proof!!!!", "deleteme", "delete me", "delete inner"};
	t_list *del_00 = ft_lstnew(array_str[4]);
	t_list *del_01 = ft_lstnew(array_str[5]);
	t_list *del_02 = ft_lstnew(array_str[6]);
	ft_lstadd_front(&my_list, del_01);
	ft_lstadd_back(&my_list, ft_lstnew(array_str[2]));
	ft_lstadd_back(&my_list, ft_lstnew(array_str[3]));
	ft_lstadd_front(&my_list, ft_lstnew(array_str[1]));
	ft_lstadd_back(&my_list, del_00);
	ft_lstadd_back(&my_list, del_02);
	ft_lstadd_front(&my_list, ft_lstnew(array_str[0]));
	printf("ft_lstsize(my_list) : %d\n", ft_lstsize(my_list));
	printf("ft_lstlast(my_list): %s\n", (char *)ft_lstlast(my_list)->content);
	ft_lstiter(my_list, (void *)&lst_show);
	printf("\n");
	ft_lstdelone(del_01, (void *)&lst_del);
	ft_lstiter(my_list, (void *)&lst_show);
	printf("\n");
	ft_lstclear(&del_02, (void *)&lst_del);
	ft_lstiter(my_list, (void *)&lst_show);
	printf("\n");
	ft_lstmap(my_list, (void *)&lst_show, (void *)&lst_del);
	ft_lstiter(my_list, (void *)&lst_show);
	printf("\n\n _________________________________________________________________");
}

void	test_35_ft_lstadd_front()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@35 - TESTING FT_LSTADD_FRONT (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_36_ft_lstsize()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@36 - TESTING FT_LSTSIZE (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_37_ft_lstlast()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@37 - TESTING FT_LSTLAST (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_38_ft_lstadd_back()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@38 - TESTING FT_LSTADD_BACK (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_39_ft_lstdelone()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@39 - TESTING FT_LSTDELONE (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_40_ft_lstclear()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@40 - TESTING FT_LSTCLEAR (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_41_ft_lstiter()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@41 - TESTING FT_LSTITER (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	test_42_ft_lstmap()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@42 - TESTING FT_LSTMAP (BONUS)\e[0m\n");
	printf("TODO\n\n _________________________________________________________________");
}

void	tester_all()
{
	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ LIBC ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
	test_00_ft_isalpha();
	test_01_ft_isdigit();
	test_02_ft_isalnum();
	test_03_ft_isascii();
	test_04_ft_isprint();
	test_05_ft_strlen();
	test_06_ft_memset();
	test_07_ft_bzero();
	test_08_ft_memcpy();
	test_09_ft_memmove();
	test_10_ft_strlcpy();
	test_11_ft_strlcat();
	test_12_ft_toupper();
	test_13_ft_tolower();
	test_14_ft_strchr();
	test_15_ft_strrchr();
	test_16_ft_strncmp();
	test_17_ft_memchr();
	test_18_ft_memcmp();
	test_19_ft_strnstr();
	test_20_ft_atoi();
	test_21_ft_calloc();
	test_22_ft_strdup();
	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ADDITIONAL - PART 2 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
	test_23_ft_substr();
	test_24_ft_strjoin();
	test_25_ft_strtrim();
	test_26_ft_split();
	test_27_ft_itoa();
	test_28_ft_strmapi();
	test_29_ft_striteri();
	test_30_ft_putchar_fd();
	test_31_ft_putstr_fd();
	test_32_ft_putendl_fd();
	test_33_ft_putnbr_fd();
	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BONUS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
	test_34_ft_lstnew();
	test_35_ft_lstadd_front();
	test_36_ft_lstsize();
	test_37_ft_lstlast();
	test_38_ft_lstadd_back();
	test_39_ft_lstdelone();
	test_40_ft_lstclear();
	test_41_ft_lstiter();
	test_42_ft_lstmap();
}

static void	show_array(char **arr)
{
	unsigned int	x;

	x = 0;
	while (arr[x])
	{
		printf("\t%d - [%s], ", x, arr[x]);
		x++;
	}
}

static char	ft_map_00(unsigned int i, char c)
{
	printf("%d", i);
	return ft_toupper(c);
}

static char	ft_map_01(unsigned int i, char c)
{
	printf("%d", i);
	return ft_tolower(c);
}

static void	ft_map_02(unsigned int i, char *c)
{
	printf("%d", i);
	*c = ft_toupper(*c);
}

static void	ft_map_03(unsigned int i, char *c)
{
	printf("%d", i);
	*c = ft_tolower(*c);
}

static void	lst_show(void *content)
{
	printf(" %s -> ", (char *)content);
}

static void lst_del(void *content)
{
	printf("%s", (char *)content);
	content = 0;
}
