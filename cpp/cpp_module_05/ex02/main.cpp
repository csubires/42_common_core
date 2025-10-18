/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:19:55 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::srand(std::time(NULL));
	{
		std::cout << "\n--- ShrubberyCreationForm ---\n";
		Bureaucrat bob("Bob", 1);
		std::cout << bob;
		ShrubberyCreationForm shrub("garden");
		std::cout << shrub;
		try
		{
			bob.executeForm(shrub);
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		bob.signForm(shrub);
		bob.executeForm(shrub);
	}
	{
		std::cout << "\n--- RobotomyRequestForm ---\n";
		Bureaucrat alice("Alice", 45);
		std::cout << alice;
		RobotomyRequestForm robot("Bender");
		std::cout << robot;
		try
		{
			alice.executeForm(robot);
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}
		alice.signForm(robot);
		alice.signForm(robot);
		for (int x = 0; x < 5; ++x)
		{
			std::cout << "Attempt #" << x + 1 << ": ";
			alice.executeForm(robot);
		}
	}
	{
		std::cout << "\n--- PresidentialPardonForm ---\n";
		Bureaucrat john("John", 6);
		std::cout << john;
		PresidentialPardonForm pardon("Marvin");
		std::cout << pardon;
		john.signForm(pardon);
		try
		{
			john.executeForm(pardon);
		} catch (std::exception &e)
		{
			std::cout << e.what();
		}
		john.increment();
		john.executeForm(pardon);
	}

	return (0);
}
