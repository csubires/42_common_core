/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/02 16:36:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("RobotomyRequestForm", 72, 45, target) { }

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &obj): AForm(obj)
{
	std::cout << "RobotomyRequestForm Copy constructor called" << std::endl;
	*this = obj;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &obj)
{
	std::cout << "RobotomyRequestForm assignation operator called" << std::endl;
	(void)obj;
	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	std::cout << "********* DRILLING NOISES *********" << std::endl;
	if (executor.getGrade() > this->gradeToExecute())
		throw RobotomyRequestForm::GradeTooHighException();
	else if (this->isSigned() == false)
		throw FormNotSignedException();
	else if(std::rand() % 2 == 0)
		std::cout << this->getTarget() <<" has been robotomized successfully." << std::endl;
	else
		std::cout << this->getTarget() <<" has not been robotomized successfully." << std::endl;
}

const char	*RobotomyRequestForm::FormNotSignedException::what() const throw()
{
	return ("RobotomyRequestForm is not signed.\n");
}
