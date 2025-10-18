/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 15:23:22 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

# define BLUE		"\e[1;34m"
# define GREEN		"\e[1;32m"
# define YELLOW		"\e[1;33m"
# define RED		"\e[1;31m"
# define MGENTA		"\e[1;35m"
# define CYAN		"\e[1;36m"
# define ENDC		"\e[1;0m"
# define CLEAR		"\e[2J\e[H"
# define RLINE		"\e[1A\e[K"

class ClapTrap
{
	private:
		std::string		name;
		unsigned int 	hit_points;
		unsigned int 	energy_points;
		unsigned int 	attack_damage;

	public:
		ClapTrap();
		~ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &copy);

		ClapTrap		&operator=(const ClapTrap &copy);
		std::string		getName();
		unsigned int 	getHitPoints();
		unsigned int 	getEnergyPoints();
		unsigned int 	getAttackDamage();
		void			attack(const std::string& target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);
		void			sethit_points(unsigned int amount);
		void			setEnergyPoints(unsigned int amount);
		void			setAttackDamage(unsigned int amount);
};

#endif
