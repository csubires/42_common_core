/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AMateria.hpp"

AMateria::AMateria() : _type("UNKNOWN")
{
	std::cout << "[C] AMateria default constructor called." << std::endl;
}

AMateria::AMateria(str const &type) : _type(type) {
	std::cout << "[C] AMateria base constructor called for type : " << this->_type << "." << std::endl;
}

AMateria::AMateria(AMateria const &src)
{
	std::cout << "[C] AMateria copy constructor called." << std::endl;
	*this = src;
}

AMateria::~AMateria()
{
	std::cout << "[D] AMateria default destructor called." << std::endl;
}

AMateria &AMateria::operator=(AMateria const &rSym)
{
	if (this != &rSym)
		this->_type = rSym._type;
	return *this;
}

str const &	AMateria::getType() const
{
	return this->_type;
}

void AMateria::use(int idx, ICharacter &target)
{
	(void) idx;
	(void) &target;
}
