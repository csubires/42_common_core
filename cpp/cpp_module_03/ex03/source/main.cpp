/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 16:05:14 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/DiamondTrap.hpp"

int main(void)
{
	DiamondTrap none;
	DiamondTrap Ally("Ally");
	DiamondTrap Enemy("Enemy");
	DiamondTrap Copy(Ally);

	none = Enemy;

	Ally.attack("Enemy");
	Enemy.takeDamage(Ally.getAttackDamage());
	Enemy.beRepaired(20);
	Enemy.attack("Ally");
	Ally.takeDamage(10);
	Ally.beRepaired(30);
	Ally.attack("Enemy");
	Ally.guardGate();
	Ally.highFivesGuys();
	Ally.whoAmI();
	Enemy.whoAmI();

	return (0);
}
