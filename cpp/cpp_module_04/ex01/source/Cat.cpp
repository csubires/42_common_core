/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat() : Animal("Cat"), CatBrain(new Brain())
{
	std::cout << GREEN << "Cat Default constructor called" << ENDC << std::endl;
}

Cat::Cat::~Cat()
{
	delete CatBrain;
	std::cout << RED << "Cat destructor called" << ENDC << std::endl;
}

Cat::Cat(Cat const &copy) : Animal(copy.type), CatBrain(new Brain())
{
	std::cout << GREEN << "Cat copy constructor called" << ENDC << std::endl;
}

Cat &Cat::operator=(Cat const &copy)
{
	std::cout << YELLOW << "Cat copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
	{
		type = copy.type;
		this->CatBrain = copy.CatBrain;
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << BLUE << " meow!!! meow!!! meow!!! " << ENDC << std::endl;
}
