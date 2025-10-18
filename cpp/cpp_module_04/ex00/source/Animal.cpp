/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << GREEN << "Animal Default constructor called" << ENDC << std::endl;
}

Animal::Animal(std::string type) : type(type)
{
	std::cout << GREEN << "Animal constructor called" << ENDC << std::endl;
}

Animal::~Animal(void)
{
	std::cout << RED << "Animal destructor called" << ENDC << std::endl;
	return;
}

Animal::Animal(Animal const &copy) : type(copy.type)
{
	std::cout << GREEN << "Animal copy constructor called" << ENDC << std::endl;
}

Animal const &Animal::operator=(Animal const &copy)
{
	std::cout << YELLOW << "Animal copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
		type = copy.type;
	return (*this);
}

std::string	Animal::getType() const
{
	return(type);
}

void Animal::makeSound(void) const
{
	std::cout << BLUE << " An unidentified animal made a sound " << ENDC << std::endl;
}
