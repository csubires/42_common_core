/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 19:28:10 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("")
{
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	std::cout << CYAN << "ScavTrap Default constructor called" << ENDC << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	std::cout << CYAN << "ScavTrap Construtor called" << ENDC << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << YELLOW << "ScapTrap destructor called" << ENDC << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &copy) : ClapTrap(copy)
{
	*this = (ScavTrap &)copy;
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &copy)
{
	std::cout <<  MGENTA << "ScavTrap copy assignment operator called" << ENDC << std::endl;
	if (this != &copy)
	{
		name = copy.name;
		hit_points = copy.hit_points;
		energy_points = copy.energy_points;
		attack_damage = copy.attack_damage;
	}
	return (*this);
}

void ScavTrap::attack(const std::string& target)
{
	if (hit_points <= 0)
	{
		std::cout << "ScavTrap " << name << " is dead. Could not attack" << std::endl;
		return;
	}
	if (energy_points <= 0 )
	{
		std::cout << "ScavTrap " << name << " has no energy points left. Could not attack" << std::endl;
		return;
	}
	std::cout << "ScavTrap " << name << " attacks " << target <<  " causing " << attack_damage << " points of damage!" << std::endl;
	energy_points -= 1;
	std::cout << "1 energy point spent on attacking" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << GREEN << "ScavTrap " << name << " is now on Gate keeper mode" << ENDC << std::endl;
}
