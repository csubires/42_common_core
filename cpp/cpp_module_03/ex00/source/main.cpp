/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/10 11:53:32 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

int main(void)
{
	ClapTrap none;
	ClapTrap Ally("Ally");
	ClapTrap Enemy("Enemy");
	ClapTrap Copy(Ally);

	none = Enemy;

	Ally.attack("Enemy");
	Enemy.takeDamage(Ally.getAttackDamage());
	Enemy.beRepaired(30);
	Enemy.attack("Ally");
	Ally.takeDamage(20);
	Ally.beRepaired(40);
	Ally.attack("Enemy");
	return (0);
}
