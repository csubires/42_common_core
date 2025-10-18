/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/18 09:25:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanB.hpp"
#include "../include/Weapon.hpp"

HumanB::HumanB(std::string name):name(name)
{
	std::cout << "The HumanA \"" <<  this->name << "\" has called the constructor" << std::endl;
}

HumanB::~HumanB()
{
	std::cout << "The HumanA \"" <<  this->name << "\" has called the destructor" << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack()
{
	if (!this->weapon)
		std::cout << "without weapon";
	else
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
}
