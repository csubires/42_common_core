/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/15 09:36:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include "Span.hpp"
#include <map>

int main()
{
	int tmp = 0;
	std::srand(std::time(0));
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "Test subject:" << std::endl;
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	{
		Span sp = Span(10000);
		std::srand(std::time(NULL));
		for (int x = 0; x < 10000; ++x)
		{
			tmp = std::rand() % 100000;
			std::cout << tmp << ", ";
			sp.addNumber(tmp);
		}
		std::cout << std::endl;
		std::cout << std::endl << "Test with 10,000 numbers:" << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp = Span(10000);
		for (int x = 0; x < 10000; ++x)
		{
			tmp = x * 2;
			std::cout << tmp << ", ";
			sp.addNumber(tmp);
		}
		std::cout << std::endl;
		std::cout << "Test with iterator range:" << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	return (0);
}
