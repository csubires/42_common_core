/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:55:55 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 08:51:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#define RESET   "\033[0m"
#define RED	 	"\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA "\033[35m"
#define CYAN	"\033[36m"
#define BOLD	"\033[1m"

Base*	generate(void);
void	identify(Base* p);
void	identify(Base& p);

void test_identification(Base *p, const std::string &test_name)
{
	std::cout << CYAN << BOLD << "\n[TEST " << test_name << "]" << RESET << std::endl;
	std::cout << YELLOW << "Pointer identification: " << RESET;
	identify(p);
	std::cout << YELLOW << "Reference identification: " << RESET;
	identify(*p);
}

void mass_generation_test(int iterations)
{
	std::cout << MAGENTA << BOLD << "\n=== MASS GENERATION TEST ("
		<< iterations << " iterations) ===" << RESET << std::endl;
	int counts[3] = {0};
	for (int x = 0; x < iterations; ++x)
	{
		Base* instance = generate();
		std::cout << BLUE << "Instance " << x+1 << ":\t" << RESET;
		if (dynamic_cast<A*>(instance)) counts[0]++;
		else if (dynamic_cast<B*>(instance)) counts[1]++;
		else if (dynamic_cast<C*>(instance)) counts[2]++;
		identify(instance);
		delete instance;
	}
	std::cout << GREEN << "\nDistribution:\n"
		<< "  A: " << counts[0] << " (" << (counts[0]*100/iterations) << "%)\n"
		<< "  B: " << counts[1] << " (" << (counts[1]*100/iterations) << "%)\n"
		<< "  C: " << counts[2] << " (" << (counts[2]*100/iterations) << "%)\n"
		<< RESET;
}

void edge_case_testing()
{
	std::cout << RED << BOLD << "\n=== EDGE CASE TESTING ===" << RESET << std::endl;
	std::cout << YELLOW << "\n[NULL POINTER TEST]" << RESET << std::endl;
	Base *nullPtr = NULL;
	std::cout << "Identifying NULL pointer: ";
	identify(nullPtr);
	try
	{
		std::cout << "Trying to identify NULL reference: ";
		identify(*nullPtr);
	} catch (const std::exception &e)
	{
		std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
	}
}

int main()
{
	std::srand(std::time(0));
	A a;
	B b;
	C c;
	test_identification(&a, "KNOWN TYPE A");
	test_identification(&b, "KNOWN TYPE B");
	test_identification(&c, "KNOWN TYPE C");
	std::cout << GREEN << BOLD << "\n=== RANDOM INSTANCE TESTS ===" << RESET << std::endl;
	for (int x = 0; x < 5; ++x)
	{
		Base* randomInstance = generate();
		std::ostringstream oss;
		oss << (x+1);
		test_identification(randomInstance, "RANDOM INSTANCE " + oss.str());
		delete randomInstance;
	}
	mass_generation_test(100);
	edge_case_testing();
	std::cout << MAGENTA << BOLD << "\n=== MEMORY CHECK ===" << RESET << std::endl;
	Base* leakCheck = generate();
	std::cout << "Generated instance for memory check (should be deleted)" << std::endl;
	delete leakCheck;

	return (0);
}
