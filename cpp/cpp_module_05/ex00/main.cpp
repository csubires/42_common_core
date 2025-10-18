/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/11 12:42:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

int main()
{
	{
		std::cout << "\n--- Testing valid construction ---\n";
		Bureaucrat b1("Alice", 1);
		Bureaucrat b2("Bob", 150);
		Bureaucrat b3("Charlie", 75);
		std::cout << b1;
		std::cout << b2;
		std::cout << b3;
	}
	{
		std::cout << "\n--- Testing invalid construction ---\n";
		try
		{
			Bureaucrat b1("InvalidHigh", 0);
			std::cout << b1;
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		try {
			Bureaucrat b2("InvalidLow", 151);
			std::cout << b2;
		} catch (std::exception &e)
		{
			std::cout << e.what();
		}
	}
	{
		std::cout << "\n--- Testing increment and decrement ---\n";
		try
		{
			Bureaucrat b("IncrementTest", 2);
			std::cout << b;
			b.increment();
			std::cout << b;
			b.increment();
			std::cout << b;
			b.increment();
			std::cout << b;
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		try {
			Bureaucrat b("DecrementTest", 149);
			std::cout << b;
			b.decrement();
			std::cout << b;
			b.decrement();
			std::cout << b;
		} catch (std::exception &e) {
			std::cout << e.what();
		}
	}
	return (0);
}
