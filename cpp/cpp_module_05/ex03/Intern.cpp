/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/11 12:48:08 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"

Intern::Intern()
{
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern &obj)
{
	std::cout << "Intern copy constructor called." << std::endl;
	if (this != &obj)
		*this = obj;
}

Intern::~Intern()
{
	std::cout << "Intern destructor called" << std::endl;
}

Intern	&Intern::operator=(const Intern &obj)
{
	(void)obj;
	std::cout << "Intern assignation operator called" << std::endl;
	return (*this);
}

AForm	*Intern::NewRobotomyRequestForm(std::string target)
{
	return (new RobotomyRequestForm(target));
}

AForm	*Intern::NewPresidentialPardonForm(std::string target)
{
	return (new PresidentialPardonForm(target));
}

AForm	*Intern::NewShrubberyCreationForm(std::string target)
{
	return (new ShrubberyCreationForm(target));
}

AForm	*Intern::makeForm(std::string form, std::string target)
{
	std::string forms[3] = { "robotomy request", "presidential pardon", "shrubbery creation" };
	AForm *(Intern::*ptr[3])(std::string) = { &Intern::NewRobotomyRequestForm, &Intern::NewPresidentialPardonForm, &Intern::NewShrubberyCreationForm };
	size_t x;

	 x = -1;
	while(++x < 3)
	{
		if(form == forms[x])
		{
			std::cout << "Intern creates " << form << std::endl;
			return (this->*ptr[x])(target);
		}
	}
	throw FormNotExistException();
	return (NULL);
}

const char	*Intern::FormNotExistException::what() const throw()
{
	return ("Form does not exist.\n");
}
