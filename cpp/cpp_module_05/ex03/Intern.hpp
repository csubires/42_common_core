/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/03 17:38:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP
# include <iostream>
# include <exception>
# include "AForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "ShrubberyCreationForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern &obj);
		~Intern();
		Intern	&operator=(const Intern &obj);
		AForm	*makeForm(std::string form, std::string target);
		AForm	*NewRobotomyRequestForm(std::string target);
		AForm	*NewPresidentialPardonForm(std::string target);
		AForm	*NewShrubberyCreationForm(std::string target);

	class FormNotExistException: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};

#endif
