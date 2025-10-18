/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:15:31 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(): name("Default"), grade_sign(150), grade_execute(150), is_signed(false)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(const Form &obj): name(obj.name), grade_sign(obj.grade_sign), grade_execute(obj.grade_execute), is_signed(obj.is_signed)
{
	std::cout << "Form object constructor called" << std::endl;
}

Form::Form(std::string name, int grade_sign, int grade_execute): name(name), grade_sign(grade_sign), grade_execute(grade_execute), is_signed(false)
{
	std::cout << "Form constructor called" << std::endl;
	if (grade_sign < 1)
		throw GradeTooHighException();
	else if (grade_sign > 150)
		throw GradeTooLowException();
	if (grade_execute < 1)
		throw GradeTooHighException();
	else if (grade_execute > 150)
		throw GradeTooLowException();
}

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

Form	&Form::operator=(const Form &obj)
{
	std::cout << "Form assignation operator called" << std::endl;
	if (this != &obj)
		this->is_signed = obj.is_signed;
	return (*this);
}

std::string Form::getName() const
{
	return (name);
}

int	Form::gradeToSign() const
{
	return (grade_sign);
}

int	Form::gradeToExecute() const
{
	return (grade_execute);
}

bool	Form::isSigned() const
{
	return (is_signed);
}

void	Form::beSigned(Bureaucrat &bureaucrat)
{
	if (is_signed)
		throw FormWasSigned();

	if(bureaucrat.getGrade() <= grade_sign)
		is_signed = true;
	else
		throw GradeTooLowException();
}

std::ostream	&operator<<(std::ostream &out, Form &obj)
{
	out << "Form: " << obj.getName() << ", Grade To Sign: " << obj.gradeToSign() \
	<< ", Grade To Execute: " << obj.gradeToExecute() << ", Signed: " << obj.isSigned() << std::endl;
	return (out);
}

const char	*Form::FormWasSigned::what() const throw()
{
	return ("The form was previously signed.\n");
}

const char	*Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high.\n");
}

const char	*Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low.\n");
}
