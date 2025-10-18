/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 10:39:21 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "iter.hpp"

template <typename T>
void show(const T &x)
{
	std::cout << x << " ";
}

template <typename T>
void incrementValue(const T &x)
{
	std::cout << x * 2 << " ";
}

void toUpper(const char &c)
{
	if (c >= 'a' && c <= 'z')
		std::cout << (char)(c - 32) << " ";
	else
		std::cout << c << " ";
}

int main() {

	int intArray[] = { 1, 2, 3, 4, 5 };
	size_t intSize = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << "Test 1 - int array (show): ";
	iter(intArray, intSize, show<int>);
	std::cout << std::endl;

	std::cout << "Test 1 - int array (double): ";
	iter(intArray, intSize, incrementValue<int>);
	std::cout << std::endl << std::endl;

	char charArray[] = {'a', 'b', 'C', 'd', 'E'};
	size_t charSize = sizeof(charArray) / sizeof(charArray[0]);

	std::cout << "Test 2 - char array (show): ";
	iter(charArray, charSize, show<char>);
	std::cout << std::endl;

	std::cout << "Test 2 - char array (toUpper): ";
	iter(charArray, charSize, toUpper);
	std::cout << std::endl << std::endl;

	std::string strArray[] = {"hello", "world", "42", "cpp"};
	size_t strSize = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << "Test 3 - string array (show): ";
	iter(strArray, strSize, show<std::string>);
	std::cout << std::endl << std::endl;

	int emptyArray[0];
	std::cout << "Test 4 - empty array (show): ";
	iter(emptyArray, 0, show<int>);
	std::cout << "(no output expected)" << std::endl;

	return (0);
}
