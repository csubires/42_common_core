/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/11 12:48:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	{
		std::cout << "\n--- Test: valid Form creation ---\n";
		try
		{
			Form f1("FormA", 50, 75);
			Form f2("FormB", 1, 1);
			Form f3("FormC", 150, 150);
			std::cout << f1;
			std::cout << f2;
			std::cout << f3;
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
	}
	{
		std::cout << "\n--- Test: invalid Form creation ---\n";
		try
		{
			Form f1("BadForm1", 0, 10);
			std::cout << f1;
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		try
		{
			Form f2("BadForm2", 10, 151);
			std::cout << f2;
		} catch (std::exception &e)
		{
			std::cout << e.what();
		}
	}
	{
		std::cout << "\n--- Test: Form::beSigned ---\n";
		Bureaucrat high("HighRank", 1);
		Bureaucrat low("LowRank", 150);
		Form form("ImportantForm", 50, 75);
		std::cout << form;
		try
		{
			std::cout << low;
			form.beSigned(low);
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		try
		{
			std::cout << high;
			form.beSigned(high);
			std::cout << "Form signed successfully by HighRank.\n";
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
	}
	{
		std::cout << "\n--- Test: Bureaucrat::signForm ---\n";
		Bureaucrat b1("Alice", 100);
		Bureaucrat b2("Bob", 10);
		Form form("Confidential", 50, 20);
		std::cout << b1;
		std::cout << b2;
		std::cout << form;
		b1.signForm(form);
		b1.signForm(form);
		b2.signForm(form);
		b2.signForm(form);
	}
	return (0);
}
