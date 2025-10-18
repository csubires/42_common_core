/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 16:48:25 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137, target) { }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &obj): AForm(obj)
{
	std::cout << "ShrubberyCreationForm Copy constructor called" << std::endl;
	*this = obj;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &obj)
{
	std::cout << "ShrubberyCreationForm assignation operator called" << std::endl;
	(void)obj;
	return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->gradeToExecute())
		throw ShrubberyCreationForm::GradeTooHighException();
	else if (this->isSigned() == false)
		throw FormNotSignedException();
	std::ofstream file;
	file.open((this->getTarget() + "_shrubbery").c_str());
	if (!file.is_open())
	{
		std::cout << "Error: could not open file" << std::endl;
		return ;
	}
	file << "    opopoo    oopoo          opopoo    oopoo          opopoo    oopoo             " << std::endl;
	file << "  oopopo oo  opopooo       oopopo oo  opopooo       oopopo oo  opopooo            " << std::endl;
	file << " oooo uuopoo ooo ooop     oooo uuopoo ooo ooop     oooo uuopoo ooo ooop           " << std::endl;
	file << " opo o opopo  sopsopo     opo o opopo  sopsopo     opo o opopo  sopsopo           " << std::endl;
	file << "  opo soopoooo o ooo       opo soopoooo o ooo       opo soopoooo o ooo            " << std::endl;
	file << "    ooo\\oo\\  /o/o            ooo\\oo\\  /o/o            ooo\\oo\\  /o/o         " << std::endl;
	file << "        \\  \\/ /                  \\  \\/ /                  \\  \\/ /           " << std::endl;
	file << "         |   /                    |   /                    |   /                  " << std::endl;
	file << "         |  |                     |  |                     |  |                   " << std::endl;
	file << "         |  |                     |  |                     |  |                   " << std::endl;
	file << "         |  |                     |  |                     |  |                   " << std::endl;
	file << "         |  |                     |  |                     |  |                   " << std::endl;
	file.close();
}

const char	*ShrubberyCreationForm::FormNotSignedException::what() const throw()
{
	return ("ShrubberyCreationForm is not signed.\n");
}
