/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/14 14:11:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "Array.hpp"

#define MAX_VAL 20

void testIntArray() {
	std::cout << "\n=== TESTING INT ARRAY ===\n";
	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];

	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}

	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (test[i] != numbers[i])
			{
				std::cerr << "Error: Copy does not match!" << std::endl;
				return ;
			}
		}
		std::cout << "✔ Copy and assignment work correctly\n";
	}
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "Error: The same values were not saved" << std::endl;
			return ;
		}
	}
	std::cout << "✔ Values stored correctly\n";
	try
	{
		numbers[-2] = 0;
	} catch(const std::exception& e) {
		std::cout << "✔ Trapped exception (negative index): " << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	} catch(const std::exception& e)
	{
		std::cout << "✔ Trapped exception (index out of bounds): " << e.what() << '\n';
	}
	delete[] mirror;
}

void	testStringArray()
{
	Array<std::string> strings(3);
	std::cout << "\n=== TESTING STRING ARRAY ===\n";
	strings[0] = "Hellow";
	strings[1] = "42";
	strings[2] = "Málaga";
	std::cout << "✔ Strings stored:\n";
	for (unsigned int i = 0; i < strings.size(); i++)
	{
		std::cout << "- " << strings[i] << '\n';
	}
	Array<std::string> copy = strings;
	copy[1] = "Málaga 2";
	std::cout << "✔ Original[1] after copy modification: " << strings[1] << '\n';
	std::cout << "✔ Copy[1] modified: " << copy[1] << '\n';
}

void 	testEmptyArray()
{
	Array<float> empty;
	std::cout << "\n=== TESTING EMPTY ARRAY ===\n";
	std::cout << "✔ Empty array size: " << empty.size() << '\n';
	try
	{
		empty[0] = 3.14f;
	} catch(const std::exception& e) {
		std::cout << "✔ Exception trapped (access to empty array): " << e.what() << '\n';
	}
}

int	main()
{
	testIntArray();
	testStringArray();
	testEmptyArray();

	return (0);
}
