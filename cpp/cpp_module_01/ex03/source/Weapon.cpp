/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 18:44:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Weapon.hpp"

Weapon::Weapon()
{
	std::cout << "The Weapon has called the constructor" << std::endl;
}

Weapon::Weapon(std::string type) : type(type)
{
	std::cout << "The Weapon \"" <<  this->type << "\" has called the constructor" << std::endl;
}

Weapon::~Weapon()
{
	std::cout << "The Weapon \"" <<  this->type << "\" has called the destructor" << std::endl;
}

const std::string Weapon::getType()
{
	return (this->type);
}

void Weapon::setType(std::string type)
{
	this->type = type;
}
