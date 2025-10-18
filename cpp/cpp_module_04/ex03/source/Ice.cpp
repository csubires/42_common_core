/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Ice.hpp"

Ice::Ice() : AMateria::AMateria("ICE")
{
	std::cout << "[C] Ice default constructor called." << std::endl;
	this->_type = AMateria::_type;
}

Ice::Ice(Ice const &src) : AMateria::AMateria(src)
{
	std::cout << "[C] Ice copy constructor called." << std::endl;
	*this = src;
}

Ice::~Ice()
{
	std::cout << "[D] Ice default destructor called." << std::endl;
}

Ice &Ice::operator=(Ice const &rSym)
{
	if (this != &rSym) {
		this->_type = rSym._type;
	}
	return (*this);
}

AMateria *Ice::clone() const
{
	return (new Ice());
}

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
