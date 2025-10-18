/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimal.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:49:33 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_ANIMAL_HPP
# define ABSTRACT_ANIMAL_HPP

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

class AbstractAnimal
{
	public:
		AbstractAnimal();
		virtual ~AbstractAnimal() = 0;
		AbstractAnimal(std::string _type);
		AbstractAnimal(AbstractAnimal const &copy);
		AbstractAnimal const	&operator=(AbstractAnimal const &copy);

		std::string				getType() const;
		virtual void			makeSound(void) const = 0;

	protected:
		std::string				type;
};

#endif
