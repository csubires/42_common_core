/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 09:07:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void)
{
	name =  "";
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
	std::cout << GREEN << "DiamondTrap default constructor was called" << ENDC << std::endl;
}

DiamondTrap::DiamondTrap(std::string const &name)
{
	this->name = name;
	ClapTrap::name = name + "_clapname";
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
	std::cout << GREEN << "DiamondTrap Constructor called" << ENDC << std::endl;
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << RED << "DiamondTrap Destructor called" << ENDC << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &copy) : ClapTrap(copy), ScavTrap(copy), FragTrap(copy)
{
	*this = copy;
	std::cout << BLUE << "DiamondTrap Copy constructor called" << ENDC << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &copy)
{
	std::cout << MGENTA << "DiamondTrap copy assignment constructor called" << ENDC << std::endl;
	if (this != &copy)
	{
		ClapTrap::name = copy.name + "_clapname";
		name = copy.name;
		hit_points = copy.FragTrap::hit_points;
		energy_points = copy.ScavTrap::energy_points;
		attack_damage = copy.FragTrap::attack_damage;
	}
	return (*this);
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap name: " << name << "; ClapTrap name: " << ClapTrap::name << ";" << std::endl;
}

void DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}
