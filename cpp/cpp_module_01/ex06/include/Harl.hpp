/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/18 17:55:24 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>

# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define YELLOW				"\033[1;33m"
# define BLUE				"\033[1;34m"
# define ENDC				"\033[0m"

class Harl
{
	private:
			void debug(void);
			void info(void);
			void warning(void);
			void error(void);

	public:
			Harl();
			~Harl();
			void complain(std::string level);
			void filtered_complain(std::string level);
};

#endif
