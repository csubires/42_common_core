/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:05:24 by csubires          #+#    #+#             */
/*   Updated: 2025/06/03 11:30:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// make
// c++ -std=c++98 -Wall -Wextra -Werror -g obj/PmergeMe.o test.cpp -o test

#include <cstdlib>
#include <ctime>
#include <climits>
#include <iomanip>
#include "PmergeMe.hpp"

void printHeader(const std::string &title)
{
	std::cout << "\n\033[1;35m===== " << title << " =====\033[0m\n";
}

void testNormalCases()
{
	printHeader("Normal Cases");
	{
		std::cout << "\n\033[1;36m--- Case 1: Small sequence (5 elements) ---\033[0m\n";
		int arr[] = {3, 5, 9, 7, 4};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		PmergeMe pm(vec, 5);
	}
	{
		std::cout << "\n\033[1;36m--- Case 2: Already sorted sequence ---\033[0m\n";
		int arr[] = {1, 2, 3, 4, 5};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		PmergeMe pm(vec, 5);
	}
	{
		std::cout << "\n\033[1;36m--- Case 3: Reverse sorted sequence ---\033[0m\n";
		int arr[] = {5, 4, 3, 2, 1};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		PmergeMe pm(vec, 5);
	}
	{
		std::cout << "\n\033[1;36m--- Case 4: Sequence with duplicates ---\033[0m\n";
		int arr[] = {2, 3, 2, 5, 2};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		PmergeMe pm(vec, 5);
	}
}

void testEdgeCases()
{
	printHeader("Edge Cases");
	{
		std::cout << "\n\033[1;36m--- Case 1: Single element ---\033[0m\n";
		std::vector<int> vec(1, 42);
		PmergeMe pm(vec, 1);
	}
	{
		std::cout << "\n\033[1;36m--- Case 2: Empty sequence (should error) ---\033[0m\n";
		std::vector<int> vec;
		try
		{
			PmergeMe pm(vec, 0);
		} catch (const std::exception &e)
		{
			std::cout << "\033[1;31mError caught: " << e.what() << "\033[0m\n";
		}
	}
	{
		std::cout << "\n\033[1;36m--- Case 3: All elements equal ---\033[0m\n";
		std::vector<int> vec(5, 7);
		PmergeMe pm(vec, 5);
	}
}

void testLargeSequences()
{
	printHeader("Large Sequences");
	{
		std::cout << "\n\033[1;36m--- Case 1: 1000 elements ---\033[0m\n";
		std::vector<int> vec;
		for (int x = 0; x < 1000; ++x)
		{
			vec.push_back(rand() % 10000);
		}
		PmergeMe pm(vec, 1000);
	}
	{
		std::cout << "\n\033[1;36m--- Case 2: 3000 elements ---\033[0m\n";
		std::vector<int> vec;
		for (int x = 0; x < 3000; ++x)
		{
			vec.push_back(rand() % 10000);
		}
		PmergeMe pm(vec, 3000);
	}
	{
		std::cout << "\n\033[1;36m--- Case 3: 5000 elements ---\033[0m\n";
		std::vector<int> vec;
		for (int x = 0; x < 5000; ++x)
		{
			vec.push_back(rand() % 10000);
		}
		PmergeMe pm(vec, 5000);
	}
}

void testErrorCases()
{
	printHeader("Error Cases");
	{
		std::cout << "\n\033[1;36m--- Case 1: Negative numbers ---\033[0m\n";
		int arr[] = {3, -1, 2};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		try
		{
			PmergeMe pm(vec, 3);
		} catch (const std::exception &e)
		{
			std::cout << "\033[1;31mError caught: " << e.what() << "\033[0m\n";
		}
	}
	{
		std::cout << "\n\033[1;36m--- Case 2: Non-numeric input ---\033[0m\n";
		std::vector<int> vec;
		try {
			PmergeMe pm(vec, 0);
		} catch (const std::exception &e)
		{
			std::cout << "\033[1;31mError caught: " << e.what() << "\033[0m\n";
		}
	}
	{
		std::cout << "\n\033[1;36m--- Case 3: Very large numbers ---\033[0m\n";
		int arr[] = {1, 2, INT_MAX};
		std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
		try
		{
			PmergeMe pm(vec, 3);
		} catch (const std::exception &e)
		{
			std::cout << "\033[1;31mError caught: " << e.what() << "\033[0m\n";
		}
	}
}

void testPerformanceComparison()
{
	printHeader("Performance Comparison");
	const int sizes[] = { 10, 100, 1000, 10000 };
	const int num_tests = sizeof(sizes)/sizeof(sizes[0]);

	for (int x = 0; x < num_tests; ++x)
	{
		int size = sizes[x];
		std::cout << "\n\033[1;36m--- Size: " << size << " elements ---\033[0m\n";
		std::vector<int> vec;
		for (int y = 0; y < size; ++y)
			vec.push_back(rand() % (size * 10));
		clock_t start = clock();
		PmergeMe pm(vec, size);
		clock_t end = clock();
		double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000;
		std::cout << "Total time for " << size << " elements: "
				  << std::fixed << std::setprecision(2) << duration << " ms\n";
	}
}

int main(int argc, char *argv[])
{
	std::srand(std::time(0));
	if (argc > 1)
	{
		std::vector<int> vector;
		int nbr;
		int x;

		for (x = 1; argv[x] != NULL; x++)
		{
			for (int y = 0; argv[x][y] != '\0'; y++)
			{
				if (!isdigit(argv[x][y]))
				{
					std::cout << "Error: Invalid character in input\n";
					return (1);
				}
			}
			nbr = atoi(argv[x]);
			if (nbr < 0)
			{
				std::cout << "Error: Negative numbers not allowed\n";
				return (1);
			}
			vector.push_back(nbr);
		}
		PmergeMe instance(vector, x - 1);
	}
	else
	{
		testNormalCases();
		testEdgeCases();
		testLargeSequences();
		testErrorCases();
		testPerformanceComparison();
	}

	return (0);
}
