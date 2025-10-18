/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:48:14 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 18:50:22 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libft.h"
# include <unistd.h>

// cc -Wall -Werror -Wextra -g unitest.c -L. -l:libft.a -o unitest.out
// valgrind --leak-check=full --show-reachable=yes -s ./unitest.out

void	ft_free_split(char **arr)
{
	int x;

	x = 0;
	while (arr[x])
		free(arr[x++]);
	free(arr);
	arr = 0;
}

int	main(void)
{
	char *debugme;
	char *word;
	char **word2;
	char *strs = "Esto es una prueba";

	debugme = NULL;
	word = ft_substr(strs, 2, 4);
	int x = 0;
	while (word[x])
	{
		printf("word> %c -> \n", word[x]);
		x++;
	}

	free(word);


	word2 = ft_split(strs, ' ');
	x = 0;
	while (word2[x])
	{
		printf("word2> %s -> \n", word2[x]);
		x++;
	}

	ft_free_split(word2);

    return (0);
}



/*
cc -Wall -Werror -Wextra unitest.c -o ./obj/unitest split.c
cc -Wall -Werror -Wextra unitest.c -o ./obj/unitest ft_strrchr.c ft_strlen.c ......
./obj/unitest

cc -Wall -Werror -Wextra unitest.c -o ./obj/unitest ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
./obj/unites
*/
