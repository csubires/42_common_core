/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
#include "Character.hpp"

typedef std::string str;

class Ice : public AMateria
{
	public:
		Ice();
		~Ice();
		Ice(Ice const &src);

		Ice					&operator=(Ice const &rSym);
		virtual AMateria	*clone() const;
		virtual void		use(ICharacter &target);

	private:
		str	_type;
};

#endif
