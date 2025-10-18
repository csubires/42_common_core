/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 11:00:08 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"

int main() {
	PhoneBook phonebook;
	std::string input;

	std::cout << CLEAR << std::endl << GREEN << "  MY AWESOME PHONEBOOK" << ENDC << std::endl;
	std::cout << YELLOW << "  ____________________" << ENDC << std::endl << std::endl;
	while (1)
	{
		input = PhoneBook::getInput(" Please enter ADD, SEARCH, or EXIT: ");
		if (input.empty() && std::cin.eof())
			break;
		if (input == "ADD")
			phonebook.add();
		else if (input == "SEARCH")
			phonebook.show();
		else if (input == "EXIT")
			break;
		else
			std::cout << RED << " Invalid option. Please enter ADD, SEARCH, or EXIT." << ENDC << std::endl;
	}
	return (0);
}
