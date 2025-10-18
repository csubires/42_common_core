/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:01:03 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

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

class Brain {

	public:
		Brain();
		~Brain();
		Brain(Brain const &copy);
		Brain	&operator=(Brain const &copy);

	protected:
		std::string ideas[100];
};

#endif
