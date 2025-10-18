/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/15 09:56:48 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <deque>
#include <list>
#include <set>
#include <vector>

void printTestHeader(const std::string& testName)
{
    std::cout << "\n\033[1;34m===== TEST: " << testName << " =====\033[0m\n";
}

template<typename Container>
void testContainer(const std::string& containerName, Container& container, int value)
{
	std::cout << "Testing " << containerName << " for value " << value << ": ";
	try
	{
		typename Container::iterator it = easyfind(container, value);
		std::cout << "\033[1;32mFound: " << *it << "\033[0m";

		typename Container::iterator next_it = it;
		++next_it;
		if (next_it != container.end())
		{
			std::cout << " (next: " << *next_it << ")";
		}
		std::cout << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << "\033[1;31m" << e.what() << "\033[0m" << std::endl;
	}
}

int main()
{
	std::vector<int>	v;
	std::list<int>		l;
	std::deque<int>		d;
	for (int x = 0; x < 10; x++)
	{
		v.push_back(x);
		l.push_back(x);
		d.push_back(x);
	}
	std::cout << "Vector: ";
	try
	{
		std::cout << *easyfind(v, 5) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cout << "List: ";
	try
	{
		std::cout << *easyfind(l, 5) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cout << "Deque: ";
	try
	{
		std::cout << *easyfind(d, 5) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cout << "Invalid: ";
	try
	{
		std::cout << *easyfind(v, 11) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	{
		printTestHeader("Vector with sequential values");
		std::vector<int> vec;
		for (int x = 0; x < 10; ++x)
		{
			vec.push_back(x * 2);
		}

		testContainer("Vector", vec, 4);
		testContainer("Vector", vec, 5);
		testContainer("Vector", vec, 0);
		testContainer("Vector", vec, 18);
	}
	{
		printTestHeader("List with random values");
		std::list<int> lst;
		lst.push_back(42);
		lst.push_back(21);
		lst.push_back(84);
		lst.push_back(10);
		lst.push_back(7);
		testContainer("List", lst, 21);
		testContainer("List", lst, 99);
		testContainer("List", lst, 42);
		testContainer("List", lst, 7);
	}
	{
		printTestHeader("Empty deque");
		std::deque<int> deq;
		testContainer("Deque", deq, 1);
	}
	{
		printTestHeader("Deque with single element");
		std::deque<int> deq;
		deq.push_back(99);
		testContainer("Deque", deq, 99);
		testContainer("Deque", deq, 100);
	}
	{
		printTestHeader("Container with duplicate values");
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(9);
		vec.push_back(3);
		vec.push_back(2);
		testContainer("Vector with duplicates", vec, 2);
	}
	{
		printTestHeader("Large container");
		std::vector<int> largeVec;
		for (int x = 0; x < 100000; ++x)
		{
			largeVec.push_back(x);
		}
		testContainer("Large vector", largeVec, 0);
		testContainer("Large vector", largeVec, 99999);
		testContainer("Large vector", largeVec, 50000);
		testContainer("Large vector", largeVec, 100000);
	}
	{
		printTestHeader("Other container types (set)");
		std::set<int> s;
		s.insert(10);
		s.insert(20);
		s.insert(30);
		testContainer("Set", s, 20);
		testContainer("Set", s, 15);
	}

	return (0);
}
