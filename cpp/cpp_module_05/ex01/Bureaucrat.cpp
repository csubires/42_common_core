/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/25 09:48:26 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("Default"), grade(150)
{
	std::cout << "Bureaucrat default constructor called." << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &obj)
{
	std::cout << "Bureaucrat copy constructor called." << std::endl;
	if (this != &obj)
		*this = obj;
}

Bureaucrat::Bureaucrat(std::string name, int grade): name(name)
{
	std::cout << "Bureaucrat constructor called." << std::endl;
	if(grade < 1)
		throw GradeTooHighException();
	if(grade > 150)
		throw GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called." << std::endl;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &obj)
{
	std::cout << "Bureaucrat assignation operator called." << std::endl;
	if (this != &obj)
		this->grade = obj.grade;
	return (*this);
}

std::string Bureaucrat::getName() const
{
	return (name);
}

int		Bureaucrat::getGrade() const
{
	return (grade);
}

void	Bureaucrat::increment()
{
	if(--grade < 1)
		throw GradeTooHighException();
}

void	Bureaucrat::decrement()
{
	if(++grade > 150)
		throw GradeTooLowException();
}

void	Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << name << " signed " << form.getName() << "." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << name << " couldn't sign " << form.getName() << \
		" because " << e.what();
	}
}

std::ostream	&operator<<(std::ostream &out, Bureaucrat &obj)
{
	out << obj.getName() << ", bureaucrat grade " << obj.getGrade() << "." << std::endl;
	return (out);
}

const char	*Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Error: A bureaucrat can't have a grade greater than 1.\n");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Error: A bureaucrat can't have a grade lower than 150.\n");
}
