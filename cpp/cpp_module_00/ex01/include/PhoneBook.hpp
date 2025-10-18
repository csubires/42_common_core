/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 10:22:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

# include <iostream>
# include <string>
# include <limits>
# include <iomanip>
# include "../include/Contact.hpp"

# define MAX_CONTACTS	8
# define COLUMN_WIDE	10

# define BLUE			"\e[1;34m"
# define GREEN			"\e[1;32m"
# define YELLOW			"\e[1;33m"
# define RED			"\e[1;31m"
# define MGENTA			"\e[1;35m"
# define CYAN			"\e[1;36m"
# define ENDC			"\e[1;0m"
# define CLEAR			"\e[2J\e[H"
# define RLINE			"\e[1A\e[K"

class PhoneBook {

	private:
		Contact contacts[MAX_CONTACTS];
		int counter;

	public:
		PhoneBook();
		~PhoneBook();
		void add();
		void show(void);
		void search();
		static std::string getInput(std::string msg);
};

#endif
