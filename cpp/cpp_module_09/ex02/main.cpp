/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 08:27:43 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 3)
		return std::cout << "Error: Usage: ./PmergeMe [int sequence]" << std::endl, 1;

	std::vector<int>	vector;
	int					nbr;
	int					x;

	for (x = 1; argv[x] != NULL; x++)
	{
		for (int y = 0; argv[x][y] != '\0'; y++)
			if (!isdigit(argv[x][y]))
				return std::cout << "Error" << std::endl, 1;
		nbr = atoi(argv[x]);
		if (nbr < 0)
			return std::cout << "Error" << std::endl, 1;
		vector.push_back(nbr);
	}

	PmergeMe instance(vector, x - 1);

	return (0);
}
