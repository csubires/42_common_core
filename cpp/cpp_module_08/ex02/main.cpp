/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 12:05:21 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <vector>

void printTitle(const std::string& title)
{
	std::cout << "\n\033[1;34m=== " << title << " ===\033[0m\n";
}

void printSubtitle(const std::string& subtitle)
{
	std::cout << "\n\033[1;36m» " << subtitle << "\033[0m\n";
}

int main()
{
	printTitle("Basic MutantStack Test");
	{
		MutantStack<int> mstack;

		mstack.push(1);
		mstack.push(2);
		mstack.push(3);

		printSubtitle("Content after pushing 1, 2, 3:");
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("Basic operations:");
		std::cout << "Top: " << mstack.top() << std::endl;
		std::cout << "Size: " << mstack.size() << std::endl;

		mstack.pop();
		printSubtitle("Content after pop:");
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	printTitle("Iterator Test");
	{
		MutantStack<int> mstack;
		for (int i = 0; i < 10; ++i)
		{
			mstack.push(i * 2);
		}

		printSubtitle("Normal iteration:");
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("Reverse iteration (using reverse iterator):");
		for (MutantStack<int>::iterator it = --mstack.end(); it != mstack.begin(); --it)
		{
			std::cout << *it << " ";
		}
		std::cout << *mstack.begin() << std::endl;
	}

	printTitle("Copy and Assignment Test");
	{
		MutantStack<int> original;
		original.push(10);
		original.push(20);
		original.push(30);

		MutantStack<int> copy(original);
		MutantStack<int> assigned;
		assigned = original;

		printSubtitle("Original:");
		for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("Copy:");
		for (MutantStack<int>::iterator it = copy.begin(); it != copy.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("Assigned:");
		for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	printTitle("Test with Different Data Types");
	{
		printSubtitle("MutantStack<double>:");
		MutantStack<double> doubleStack;
		doubleStack.push(3.14);
		doubleStack.push(2.71);
		doubleStack.push(1.618);
		for (MutantStack<double>::iterator it = doubleStack.begin(); it != doubleStack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("MutantStack<std::string>:");
		MutantStack<std::string> stringStack;
		stringStack.push("Hello");
		stringStack.push("World");
		stringStack.push("C++");
		for (MutantStack<std::string>::iterator it = stringStack.begin(); it != stringStack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	printTitle("Edge Case Tests");
	{
		printSubtitle("Empty stack:");
		MutantStack<int> emptyStack;
		std::cout << "Size: " << emptyStack.size() << std::endl;
		std::cout << "Empty: " << (emptyStack.empty() ? "true" : "false") << std::endl;

		printSubtitle("Stack with single element:");
		MutantStack<int> singleStack;
		singleStack.push(42);
		std::cout << "Size: " << singleStack.size() << std::endl;
		std::cout << "Elements: ";
		for (MutantStack<int>::iterator it = singleStack.begin(); it != singleStack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	printTitle("Comparison with std::list");
	{
		MutantStack<int> mstack;
		std::list<int> lst;

		for (int i = 0; i < 5; ++i)
		{
			mstack.push(i);
			lst.push_back(i);
		}

		printSubtitle("MutantStack:");
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		printSubtitle("std::list:");
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	return (0);
}
