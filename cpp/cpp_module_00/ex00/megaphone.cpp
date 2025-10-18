/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:35:54 by csubires          #+#    #+#             */
/*   Updated: 2025/02/19 18:39:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

static void	toUpperPrint(std::string str)
{
	int	x = 0;

	while (str[x])
		std::cout << char(std::toupper(str[x++]));
}

int main(int argc, char **argv)
{
	int x = 1;

	if (argc == 1)
		toUpperPrint((char *)"* LOUD AND UNBEARABLE FEEDBACK NOISE *");
	while (x < argc)
		toUpperPrint(argv[x++]);
	std::cout << std::endl;
}
