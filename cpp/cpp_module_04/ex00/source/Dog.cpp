/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << GREEN << "Dog Default constructor called" << ENDC << std::endl;
}

Dog::Dog::~Dog()
{
	std::cout << RED << "Dog destructor called" << ENDC << std::endl;
}

Dog::Dog(Dog const &copy) : Animal(copy.type)
{
	std::cout << GREEN << "Dog copy constructor called" << ENDC << std::endl;
}

Dog &Dog::operator=(Dog const &copy)
{
	std::cout << YELLOW << "Dog copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
	{
		type = copy.type;
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << BLUE << " woof!!! woof!!! woof!!! " << ENDC << std::endl;
}
