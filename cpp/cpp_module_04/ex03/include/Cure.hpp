/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "Character.hpp"

typedef std::string str;

class Cure : public AMateria
{
	public:
		Cure();
		~Cure();
		Cure(Cure const &src);

		Cure 				&operator=(Cure const &rSym);

		virtual AMateria	*clone() const;
		virtual void		use(ICharacter &target);

	private:
		str	_type;
};

#endif
