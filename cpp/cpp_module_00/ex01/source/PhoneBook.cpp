/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/05 13:01:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"

std::string PhoneBook::getInput(std::string msg)
{
	std::string input;

	if (std::cin.eof())
		return ("");
	std::cout << std::endl << MGENTA << msg << ENDC;
	if (!std::getline(std::cin, input)) {
		if (std::cin.eof())
			std::cerr << RED << " EOF detected. Exiting input process." << ENDC << std::endl;
		else
			std::cerr << RED << " Error: Invalid input detected." << ENDC << std::endl;
		return ("");
	}
	input.erase(0, input.find_first_not_of(" \t\r\n"));
	input.erase(input.find_last_not_of(" \t\r\n") + 1);
	if (input.empty())
		return ("");
	return (input);
}

static int isNumber(const std::string str) {
	for (size_t x = 0; x < str.length(); x++)
		if (!std::isdigit(str[x]))
			return (0);
	return (1);
}

static std::string	truncateStr(std::string str)
{
	if (str.length() > COLUMN_WIDE)
		return (str.substr(0, COLUMN_WIDE - 1) + ".");
	return (str);
}

PhoneBook::PhoneBook(void)
{
	this->counter = 0;
	for(size_t x = 0; x < MAX_CONTACTS; x++)
		this->contacts[x].setAvalible(false);
	std::cout << std::endl << CYAN << " PhoneBook has been inicialized" << ENDC << std::endl;
}

PhoneBook::~PhoneBook(void)
{
	std::cout << std::endl << CYAN << " PhoneBook has been closed" << ENDC << std::endl;
}

void	PhoneBook::add()
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone;
	std::string secret;

	std::cout << CLEAR << std::endl;;
	std::cout << YELLOW << " " << ENDC << std::endl;

	while (1)
	{
		first_name = PhoneBook::getInput(" What is your First Name?: ");
		if (!first_name.empty())
			break;
		if (std::cin.eof())
			return;
		std::cout << RLINE << RED << "  Invalid input. Please try again." << ENDC << std::endl;
	}

	while (1)
	{
		last_name = PhoneBook::getInput(" What is your Last Name?: ");
		if (!last_name.empty())
			break;
		if (std::cin.eof())
			return;
		std::cout << RLINE << RED << "  Invalid input. Please try again." << ENDC << std::endl;
	}

	while (1)
	{
		nickname = PhoneBook::getInput(" What is your Nickname?: ");
		if (!nickname.empty())
			break;
		if (std::cin.eof())
			return;
		std::cout << RLINE << RED << "  Invalid input. Please try again." << ENDC << std::endl;
	}

	while (1)
	{
		phone = PhoneBook::getInput(" What is your Phone Number? (Only Numbers): ");
		if (!phone.empty() && isNumber(phone))
			break;
		if (std::cin.eof())
			return;
		std::cout << RLINE << RED << "  Invalid input. Please try again." << ENDC << std::endl;
	}

	while (1)
	{
		secret = PhoneBook::getInput(" What is your Darkest Secret?: ");
		if (!secret.empty())
			break;
		if (std::cin.eof())
			return;
		std::cout << RED << "  Invalid input. Please try again." << ENDC << std::endl;
	}

	this->counter %= MAX_CONTACTS;
	this->contacts[this->counter].setFirstName(first_name);
	this->contacts[this->counter].setLastName(last_name);
	this->contacts[this->counter].setNickname(nickname);
	this->contacts[this->counter].setPhoneNumber(phone);
	this->contacts[this->counter].setDarkestSecret(secret);
	this->contacts[this->counter].setAvalible(true);
	this->counter++;
}

void	PhoneBook::search(void)
{
	int			index;

	std::cout << std::endl << YELLOW << " Enter the index:" << ENDC << std::endl;
	std::cin >> index;
	std::cout << CLEAR << std::endl;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (index > 0 && index <= MAX_CONTACTS && this->contacts[index - 1].isSet())
	{
		std::cout << BLUE << "First Name:\t" << ENDC << this->contacts[index - 1].getFirstName() << std::endl;
		std::cout << BLUE << "Last Name:\t" << ENDC << this->contacts[index - 1].getLastName() << std::endl;
		std::cout << BLUE << "Nickname:\t" << ENDC << this->contacts[index - 1].getNickname() << std::endl;
		std::cout << BLUE << "Phone Number:\t" << ENDC << this->contacts[index - 1].getPhoneNumber() << std::endl;
		std::cout << BLUE << "Darkest Secret:\t" << ENDC << this->contacts[index - 1].getDarkestSecret() << std::endl << std::endl;
	}
	else
		std::cout << RED << " There is no contact for the index " << index << ENDC << std::endl << std::endl;
}

void	PhoneBook::show(void)
{
	std::cout << CLEAR << std::endl;

	std::cout << YELLOW << "┌──────────┬──────────┬──────────┬──────────┐" << ENDC << std::endl;
	std::cout << YELLOW << "│" << BLUE << std::setw(COLUMN_WIDE) << truncateStr("Index") << ENDC;
	std::cout << YELLOW << "│" << BLUE << std::setw(COLUMN_WIDE) << truncateStr("First Name") << ENDC;
	std::cout << YELLOW << "│" << BLUE << std::setw(COLUMN_WIDE) << truncateStr("Last Name") << ENDC;
	std::cout << YELLOW << "│" << BLUE << std::setw(COLUMN_WIDE) << truncateStr("Nickname") << ENDC;
	std::cout << YELLOW << "│" << ENDC << std::endl;
	std::cout << YELLOW << "├──────────┼──────────┼──────────┼──────────┤" << ENDC << std::endl;

	for(size_t x = 0; x < MAX_CONTACTS; x++)
	{
		if (!this->contacts[x].isSet())
			break;
		std::cout << YELLOW << "│" ENDC << std::setw(COLUMN_WIDE) << (x + 1);
		std::cout << YELLOW << "│" ENDC << std::setw(COLUMN_WIDE) << truncateStr(this->contacts[x].getFirstName());
		std::cout << YELLOW << "│" ENDC << std::setw(COLUMN_WIDE) << truncateStr(this->contacts[x].getLastName());
		std::cout << YELLOW << "│" ENDC << std::setw(COLUMN_WIDE) << truncateStr(this->contacts[x].getNickname());
		std::cout << YELLOW << "│" << ENDC << std::endl;
	}
	std::cout << YELLOW << "└──────────┴──────────┴──────────┴──────────┘" << ENDC << std::endl;
	this->search();
}
