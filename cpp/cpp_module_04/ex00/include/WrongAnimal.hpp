/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/17 09:21:06 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

# define BLUE		"\e[1;34m"
# define GREEN		"\e[1;32m"
# define YELLOW		"\e[1;33m"
# define RED		"\e[1;31m"
# define MGENTA		"\e[1;35m"
# define CYAN		"\e[1;36m"
# define ENDC		"\e[1;0m"
# define CLEAR		"\e[2J\e[H"
# define RLINE		"\e[1A\e[K"

class WrongAnimal
{
	public:
		WrongAnimal(void);
		virtual ~WrongAnimal(void);
		WrongAnimal(std::string type);
		WrongAnimal(WrongAnimal const &copy);
		WrongAnimal		&operator=(WrongAnimal const &copy);

		std::string		getType() const;
		void			makeSound(void) const;

	protected:
		std::string	type;
};

#endif
