/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:32:28 by csubires          #+#    #+#             */
/*   Updated: 2025/06/03 09:59:57 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// make
// c++ -std=c++98 -Wall -Wextra -Werror -g obj/BitcoinExchange.o test.cpp -o test

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "BitcoinExchange.hpp"

void runTest(const std::string &inputFilename)
{
	std::cout << "\n\033[1;34m=== TESTING FILE: " << inputFilename << " ===\033[0m\n";
	BitcoinExchange exchange(inputFilename);
	exchange.run();
}

void createTestFile(const std::string &filename, const std::string &content)
{
	std::ofstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Could not create test file: " << filename << std::endl;
		exit(1);
	}
	file << content;
	file.close();
}

int main()
{
	createTestFile("test_valid.txt",
		"date | value\n"
		"2011-01-03 | 3\n"
		"2011-01-03 | 0\n"
		"2022-03-15 | 42.42\n"
		"2023-12-31 | 1000\n");

	createTestFile("test_errors.txt",
		"date | value\n"
		"2010-01-01 | 1\n"
		"2011-01-03 | -5\n"
		"2011-01-03 | 1001\n"
		"2009-01-01 | 1\n"
		"2024-01-01 | 1\n"
		"invalid_date | 1\n"
		"2011-01-03 | not_a_number\n");

	createTestFile("test_edge_cases.txt",
		"date | value\n"
		"2011-01-03 | 0.0001\n"
		"2011-01-03 | 999.9999\n"
		"2011-01-03 | 1000\n"
		"2011-01-03 | 1000.0001\n");

	runTest("test_valid.txt");
	runTest("test_errors.txt");
	runTest("test_edge_cases.txt");
	runTest("non_existent_file.txt");

	std::remove("test_valid.txt");
	std::remove("test_errors.txt");
	std::remove("test_edge_cases.txt");

	return (0);
}
