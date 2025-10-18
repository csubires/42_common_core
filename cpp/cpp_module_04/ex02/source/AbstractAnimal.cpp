/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimal.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AbstractAnimal.hpp"

AbstractAnimal::AbstractAnimal(std::string type) : type(type)
{
	std::cout << GREEN << "AbstractAnimal type Default constructor called" << ENDC << std::endl;
}

AbstractAnimal::~AbstractAnimal(void)
{
	std::cout << RED << "AbstractAnimal destructor called" << ENDC << std::endl;
	return;
}

std::string	AbstractAnimal::getType() const
{
	return(type);
}
