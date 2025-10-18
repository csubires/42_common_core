/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:54:31 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 20:48:46 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>


#ifdef __LINUX__
 #include "linux/limits.h"
 void	pwd()
#endif

#include "get_next_line.h"
// #include "get_next_line_bonus.h"

/*	MANDATORY	*/
void	test_00_get_next_line();

/*	BONUS	*/
void	test_02_get_next_line_bonus();

/*	UTILS	*/
/*	OTHERS	*/
void	tester_all();
void	pwd();

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{	char *arg = argv[1];
		// printf("\e[1;1H\e[2J");
		printf("\n OPTION SELECTED: %s", arg);
		if (strcmp(arg, "0") == 0 || strcmp(arg, "line") == 0)	 				{ test_00_get_next_line(); }
		else if (strcmp(arg, "1") == 0 || strcmp(arg, "line_bonus") == 0)	 		{ test_02_get_next_line_bonus(); }
		else if (strcmp(arg, "99") == 0 || strcmp(arg, "all") == 0)	 					{ tester_all(); }
		else { printf("¡ ERROR : FUNCTION \"%s\" NOT FOUND!\n", arg); }
	}
	return (0);
}

void	test_00_get_next_line()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 00 - TESTING GET_NEXT_LINE (MANDATORY)\e[0m\n");
	unsigned int	x = 0;
	char			*name_file = "tests/test_00.txt";
	int				fd_00 = open(name_file, O_RDONLY);
	char			*line = "";

	printf("NAME: %s, ID FILE: %d, BUFFER SIZE: %d\n\n", name_file, fd_00, BUFFER_SIZE);
	while (line)
	{
		line = get_next_line(fd_00);
		printf("Line: %d\t[%s]\n", ++x, line);
		free(line);
	}
	close(fd_00);
	printf("\n\n _________________________________________________________________");
}

void	test_02_get_next_line_bonus()
{
	printf("\n \e[33m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 02 - TESTING GET_NEXT_LINE_BONUS (BONUS)\e[0m\n");
	char			*name_file_00 = "tests/test_00.txt";
	char			*name_file_01 = "tests/test_01.txt";
	char			*name_file_02 = "tests/test_02.txt";
	char			*name_file_03 = "tests/test_03.txt";
	char			*line;
	unsigned int	x = 0;
	int				fd_00 = open(name_file_00, O_RDONLY);
	int				fd_01 = open(name_file_01, O_RDONLY);
	int				fd_02 = open(name_file_02, O_RDONLY);
	int				fd_03 = open(name_file_03, O_RDONLY);
	x = 1;
	printf("NAME: %s, ID FILE: %d, BUFFER SIZE: %d\n", name_file_00, fd_00, BUFFER_SIZE);
	printf("NAME: %s, ID FILE: %d, BUFFER SIZE: %d\n", name_file_01, fd_01, BUFFER_SIZE);
	printf("NAME: %s, ID FILE: %d, BUFFER SIZE: %d\n", name_file_02, fd_02, BUFFER_SIZE);
	printf("NAME: %s, ID FILE: %d, BUFFER SIZE: %d\n\n", name_file_03, fd_03, BUFFER_SIZE);
	while (x < 10)
	{
		line = get_next_line(fd_02);
			printf("File: %d, Line: %d\t[%s]\n", fd_02, x, line);
		free(line);
			line = get_next_line(fd_03);
			printf("File: %d, Line: %d\t[%s]\n", fd_03, x, line);
		free(line);
		line = get_next_line(fd_00);
			printf("File: %d, Line: %d\t[%s]\n", fd_00, x, line);
		free(line);
		line = get_next_line(fd_01);
			printf("File: %d, Line: %d\t[%s]\n", fd_01, x, line);
		free(line);
		x++;
	}
	close(fd_00);
	close(fd_01);
	close(fd_02);
	close(fd_03);
	printf("\n\n _________________________________________________________________");
}

void	tester_all()
{
	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ MANDATORY ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
	test_00_get_next_line();
	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BONUS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
	test_02_get_next_line_bonus();
}

// ------------------------------- FUNCTIONS AUX TESTER

#ifdef __LINUX__
void	pwd()
{
	char	cwd[PATH_MAX];
	printf(" Dir. Actual: %s\n\n",getcwd(cwd, sizeof(cwd)));
}
#endif

#ifdef __APPLE__
void checkLeaks() {
	int pid = getpid();
	char leakscmd[50];
	snprintf(leakscmd,50,"leaks %d",pid);
	printf("Testing for leaks: %s\n",leakscmd);
	system(leakscmd);
	printf("Press any key to continue (may want to attach MallocDebug...)\n");
	getc(stdin);
}
#endif
