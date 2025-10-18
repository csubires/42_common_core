/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:53:40 by csubires          #+#    #+#             */
/*   Updated: 2025/06/03 10:41:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// make
// c++ -std=c++98 -Wall -Wextra -Werror -g obj/RPN.o test.cpp -o test

#include <iostream>
#include <string>
#include <vector>
#include "RPN.hpp"

void runTest(const std::string& expression, bool expectError = false)
{
	std::cout << "\n\033[1;34m=== TEST: \"" << expression << "\" ===\033[0m\n";
	try
	{
		RPN rpn(expression);
		rpn.calculate();
		if (expectError)
		{
			std::cout << "\033[1;31mFAIL: Expected error but got result\033[0m\n";
		}
	}
	catch (const std::exception &e)
	{
		if (!expectError)
		{
			std::cout << "\033[1;31mFAIL: Unexpected error: \"" << e.what() << "\"\033[0m\n";
		}
		else
		{
			std::cout << "\033[1;32mPASS: Correctly detected error: \"" << e.what() << "\"\033[0m\n";
		}
	}
}

int main()
{
	runTest("8 9 * 9 - 9 - 9 - 4 - 1 +");
	runTest("7 7 * 7 -");
	runTest("1 2 * 2 / 2 * 2 4 - +");
	runTest("(1 + 1)", true);
	runTest("8 9 *");
	runTest("7 7 * 7 -");
	runTest("1 2 * 2 / 2 *");
	runTest("5 1 2 + 4 * +");
	runTest("2 5 * 4 + 3 2 * 1 + /");
	runTest("1 +", true);
	runTest("1 2 3 +", true);
	runTest("1 2 &", true);
	runTest("1 2 + 3 * -", true);
	runTest("(1 + 1)", true);
	runTest("", true);
	runTest("1 0 /", true);
	runTest("999999 1 +");
	runTest("9 9 * 9 * 9 *");
	runTest("1 2 3 4 5 * * * *");

	return (0);
}
