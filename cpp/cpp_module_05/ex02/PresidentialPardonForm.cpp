/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/02 16:36:59 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target): AForm("PresidentialPardonForm", 25, 5, target) { }

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &obj): AForm(obj)
{
	std::cout << "PresidentialPardonForm Copy constructor called" << std::endl;
	*this = obj;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm destructor called" << std::endl;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &obj)
{
	std::cout << "PresidentialPardonForm assignation operator called" << std::endl;
	(void)obj;
	return (*this);
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->gradeToExecute())
		throw PresidentialPardonForm::GradeTooHighException();
	else if (this->isSigned() == false)
		throw FormNotSignedException();
	else
		std::cout << this->getTarget() << " has been pardoned by Zafod Beeblebrox" << std::endl;
}

const char	*PresidentialPardonForm::FormNotSignedException::what() const throw()
{
	return ("PresidentialPardonForm is not signed.\n");
}
