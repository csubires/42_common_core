/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Ice.hpp"
#include "Cure.hpp"

typedef std::string str;

class ICharacter
{
	public:
		virtual ~ICharacter();

		virtual str const 	&getName() const = 0;
		virtual void		equip(AMateria *m) = 0;
		virtual void		unequip(int idx) = 0;
		virtual void		use(int idx, ICharacter &target) = 0;
};

class Character : public ICharacter
{
	public:
		Character(str name);
		virtual	~Character();
		Character(Character const &src);

		Character &			operator=(Character const &rSym);
		virtual str const  &getName() const;
		virtual void		equip(AMateria *m);
		virtual void		unequip(int idx);
		virtual void		use(int idx, ICharacter &target);

	private:
		int			_idxTotal;
		str			_name;
		AMateria	*_inventory[4];
};

#endif
