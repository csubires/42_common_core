/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:19:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): name("Default"), grade_sign(150), grade_execute(150), target("DefaultTarget"), is_signed(false)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(const AForm &obj): name(obj.name), grade_sign(obj.grade_sign), grade_execute(obj.grade_execute), target(obj.target), is_signed(obj.is_signed)
{
	std::cout << "AForm object constructor called" << std::endl;
}

AForm::AForm(std::string name, int grade_sign, int grade_execute, std::string target): name(name), grade_sign(grade_sign), grade_execute(grade_execute), target(target), is_signed(false)
{
	std::cout << "AForm constructor called" << std::endl;
	if (grade_sign < 1)
		throw GradeTooHighException();
	else if (grade_sign > 150)
		throw GradeTooLowException();
	if (grade_execute < 1)
		throw GradeTooHighException();
	else if (grade_execute > 150)
		throw GradeTooLowException();
}

AForm::~AForm()
{
	std::cout << "AForm destructor called" << std::endl;
}

AForm	&AForm::operator=(const AForm &obj)
{
	std::cout << "AForm assignation operator called" << std::endl;
	if (this != &obj)
		this->is_signed = obj.is_signed;
	return (*this);
}

std::string AForm::getName() const
{
	return (name);
}

std::string AForm::getTarget() const
{
	return (target);
}

int	AForm::gradeToSign() const
{
	return (grade_sign);
}

int	AForm::gradeToExecute() const
{
	return (grade_execute);
}

bool	AForm::isSigned() const
{
	return (is_signed);
}

void	AForm::beSigned(Bureaucrat &bureaucrat)
{
	if (is_signed)
		throw FormWasSigned();

	if(bureaucrat.getGrade() <= grade_sign)
		is_signed = true;
	else
		throw GradeTooLowException();
}

std::ostream	&operator<<(std::ostream &out, AForm &obj)
{
	out << "AForm: " << obj.getName() << ", Grade To Sign: " << obj.gradeToSign() \
	<< ", Grade To Execute: " << obj.gradeToExecute() << ", Signed: " << obj.isSigned() << std::endl;
	return (out);
}

const char	*AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high.\n");
}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("Grade is too low.\n");
}

const char	*AForm::FormWasSigned::what() const throw()
{
	return ("The form was previously signed.\n");
}
