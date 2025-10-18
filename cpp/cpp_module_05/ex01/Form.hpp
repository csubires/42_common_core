/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:14:09 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP
# include <iostream>
# include <exception>

class Bureaucrat;

class Form
{
	private:
		const std::string	name;
		const int			grade_sign;
		const int			grade_execute;
		bool				is_signed;

	public:
		Form();
		Form(const Form &obj);
		Form(std::string name, int grade_sign, int grade_execute);
		~Form();
		Form		&operator=(const Form &obj);
		std::string	getName() const;
		int			gradeToSign() const;
		int			gradeToExecute() const;
		bool		isSigned() const;
		void		beSigned(Bureaucrat &bureaucrat);

	class FormWasSigned: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

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

std::ostream	&operator<<(std::ostream &out, Form &obj);

#endif
