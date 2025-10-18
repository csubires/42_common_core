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

Dog::Dog() : Animal("Dog"), DogBrain(new Brain())
{
	std::cout << GREEN << "Dog Default constructor called" << ENDC << std::endl;
}

Dog::Dog::~Dog()
{
	delete DogBrain;
	std::cout << RED << "Dog destructor called" << ENDC << std::endl;
}

Dog::Dog(Dog const &copy) : Animal(copy.type)
{
	this->DogBrain = new Brain(*copy.DogBrain);
	std::cout << GREEN << "Dog copy constructor called" << ENDC << std::endl;
}

Dog &Dog::operator=(Dog const &copy)
{
	std::cout << YELLOW << "Dog copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
	{
		type = copy.type;
		DogBrain = copy.DogBrain;
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << BLUE << " woof!!! woof!!! woof!!! " << ENDC << std::endl;
}
