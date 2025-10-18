/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal("WrongCat")
{
	std::cout << GREEN << "WrongCat Default constructor called" << ENDC << std::endl;
}
WrongCat::~WrongCat(void)
{
	std::cout << RED << "WrongCat destructor called" << ENDC << std::endl;
}

WrongCat::WrongCat(std::string type) : WrongAnimal(type)
{
		std::cout << GREEN << "WrongCat constructor called" << ENDC << std::endl;
}

WrongCat::WrongCat(WrongCat const &copy) : WrongAnimal(copy.type)
{
	std::cout << GREEN << "WrongCat copy constructor called" << ENDC << std::endl;
}

WrongCat	&WrongCat::operator=(WrongCat const &copy)
{
	std::cout << YELLOW << "WrongCat copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
	{
		type = copy.type;
	}
	return (*this);
}

void	WrongCat::makeSound(void) const
{
		std::cout << BLUE << " wrong meow!!! wrong meow!!! wrong meow!!! " << ENDC << std::endl;
}
