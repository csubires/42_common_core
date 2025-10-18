/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/10 11:52:13 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : name(name), hit_points(10), energy_points(10), attack_damage(0)
{
	std::cout << GREEN << "Constructor called" << ENDC << std::endl;
}

ClapTrap::ClapTrap() : name(""), hit_points(10), energy_points(10), attack_damage(0)
{
	std::cout << GREEN << "Default constructor called" << ENDC << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << RED << "Destructor called" << ENDC << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
{
	std::cout << BLUE << "ClapTrap Copy constructor called" << ENDC << std::endl;
	*this = (ClapTrap &)copy;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &copy)
{
	std::cout << MGENTA << "ClapTrap Copy Assignment constructor called" << ENDC << std::endl;
	if (this != &copy)
	{
		this->name = copy.name;
		this->hit_points = copy.hit_points;
		this->energy_points = copy.energy_points;
		this->attack_damage = copy.attack_damage;
	}
	return (*this);
}

void	ClapTrap::attack(const std::string& target)
{
	if (hit_points <= 0)
	{
		std::cout << YELLOW << "ClapTrap " << name << " is dead. Could not attack" << ENDC << std::endl;
		return;
	}
	if (energy_points <= 0 )
	{
		std::cout <<  YELLOW << "ClapTrap " << name << " has no energy points left. Could not attack" << ENDC << std::endl;
		return;
	}
	std::cout <<  YELLOW << "ClapTrap " << name << " attacks " << target <<  " causing " << attack_damage << " points of damage!" << ENDC << std::endl;
	energy_points -= 1;
	std::cout <<  YELLOW << "1 energy point spent on attacking" << ENDC << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (hit_points < amount)
		hit_points = 0;
	else
		hit_points -= amount;
	std::cout << RED << "ClapTrap " << name << " was damaged by " << amount << ". Now has "<< hit_points << " Hit points(health) left" << ENDC << std::endl;
	return ;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (energy_points <= 0)
	{
		std::cout << CYAN << "ClapTrap " << name << " has no energy points left. Could not be repaired" << ENDC << std::endl;
		return ;
	}
	else if (hit_points <= 0)
	{
		std::cout << CYAN << "ClapTrap " << name << " is dead. Could not be repaired" << ENDC << std::endl;
		return ;
	}
	hit_points += amount;
	energy_points -= 1;
	std::cout << CYAN << "ClapTrap " << name <<  " repaired " << amount << " of Hit Points(health). Now has "<< hit_points << " Hit points(health) left" << std::endl;
	std::cout << CYAN << "1 energy point spent on repairing. Now has " << energy_points << " left" << ENDC << std::endl;
}

std::string ClapTrap::getName()
{
	return (name);
}

unsigned int	ClapTrap::getHitPoints()
{
	return (hit_points);
}

unsigned int	ClapTrap::getEnergyPoints()
{
	return (energy_points);
}

unsigned int	ClapTrap::getAttackDamage()
{
	return (attack_damage);
}

void	ClapTrap::sethit_points(unsigned int amount)
{
	hit_points = amount;
}

void	ClapTrap::setEnergyPoints(unsigned int amount)
{
	energy_points = amount;
}

void	ClapTrap::setAttackDamage(unsigned int amount)
{
	attack_damage = amount;
}
