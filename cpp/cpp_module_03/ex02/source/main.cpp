/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 15:50:15 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

int main(void)
{
	FragTrap none;
	FragTrap Ally("Ally");
	FragTrap Enemy("Enemy");
	FragTrap Copy(Ally);

	none = Enemy;

	Ally.attack("Enemy");
	Enemy.takeDamage(Ally.getAttackDamage());
	Enemy.beRepaired(20);
	Enemy.attack("Ally");
	Ally.takeDamage(10);
	Ally.beRepaired(30);
	Ally.attack("Enemy");
	Ally.highFivesGuys();

	return (0);
}
