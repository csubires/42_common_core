/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("WrongAnimal")
{
	std::cout << GREEN << "WrongAnimal Default constructor called" << ENDC << std::endl;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << RED << "WrongAnimal destructor called" << ENDC << std::endl;
}

WrongAnimal::WrongAnimal(std::string _type) : type(_type)
{
	std::cout << GREEN << "WrongAnimal constructor called" << ENDC << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &copy) : type(copy.type)
{
	std::cout << GREEN << "WrongAnimal copy constructor called" << ENDC << std::endl;
}

WrongAnimal	&WrongAnimal::operator=(WrongAnimal const &copy)
{
	if (this != &copy)
		type = copy.type;
	std::cout << YELLOW << "WrongAnimal copy operator assignment called" << ENDC << std::endl;
	return (*this);
}

std::string WrongAnimal::getType() const
{
	return (type);
}

void WrongAnimal::makeSound(void) const
{
	std::cout << BLUE << " An unidentified Wrong animal made a sound " << std::endl;
}
