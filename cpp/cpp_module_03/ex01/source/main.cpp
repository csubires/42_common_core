/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/09 20:29:15 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include "../include/ScavTrap.hpp"

int main(void)
{
	ScavTrap none;
	ScavTrap Ally("Ally");
	ScavTrap Enemy("Enemy");
	ScavTrap Copy(Ally);

	none = Enemy;

	Ally.attack("Enemy");
	Enemy.takeDamage(Ally.getAttackDamage());
	Enemy.beRepaired(30);
	Enemy.attack("Ally");
	Ally.takeDamage(20);
	Ally.beRepaired(40);
	Ally.attack("Enemy");
	Ally.guardGate();

	return (0);
}
