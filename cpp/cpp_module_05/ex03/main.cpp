/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:23:20 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

void test_form_creation_and_execution(std::string formName, std::string target)
{
	try {
		Intern intern;
		Bureaucrat boss("The Boss", 1);
		std::cout << boss;
		AForm *form = intern.makeForm(formName, target);

		if (!form)
			return ;
		std::cout << *form;
		boss.signForm(*form);
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what();
	}
}

void test_invalid_form()
{
	try
	{
		Intern intern;
		AForm *invalid = intern.makeForm("do taxes", "Nobody");
		delete invalid;
	}
	catch (std::exception &e)
	{
		std::cout << "Caught expected error for invalid form: " << e.what();
	}
}

int main()
{
	std::srand(std::time(NULL));
	test_form_creation_and_execution("shrubbery creation", "home");
	std::cout << std::endl;
	test_form_creation_and_execution("robotomy request", "Bender");
	std::cout << std::endl;
	test_form_creation_and_execution("presidential pardon", "Arthur Dent");
	std::cout << std::endl;
	test_invalid_form();
	return (0);
}
