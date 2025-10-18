/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 10:21:31 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP
# include <iostream>
# include <exception>

class Bureaucrat;

class AForm
{
	private:
		const std::string	name;
		const int			grade_sign;
		const int			grade_execute;
		const std::string	target;
		bool				is_signed;

	public:
		AForm();
		AForm(const AForm &obj);
		AForm(std::string name, int grade_sign, int grade_execute, std::string target);
		virtual ~AForm();
		AForm			&operator=(const AForm &obj);
		std::string		getName() const;
		std::string		getTarget() const;
		int				gradeToSign() const;
		int				gradeToExecute() const;
		bool			isSigned() const;
		void			beSigned(Bureaucrat &bureaucrat);
		virtual void	execute(Bureaucrat const & executor) const = 0;

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

std::ostream	&operator<<(std::ostream &out, AForm &obj);

#endif
