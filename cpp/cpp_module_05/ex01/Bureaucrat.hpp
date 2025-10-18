/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/02 15:11:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP
# include <iostream>
# include <exception>
# include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat &obj);
		Bureaucrat(std::string name, int grade);
		~Bureaucrat();
		Bureaucrat		&operator=(const Bureaucrat &obj);
		std::string		getName() const;
		int				getGrade() const;
		void			increment();
		void			decrement();
		void			signForm(Form &form);

	class GradeTooHighException: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class GradeTooLowException: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};

std::ostream	&operator<<(std::ostream &out, Bureaucrat &obj);

#endif
