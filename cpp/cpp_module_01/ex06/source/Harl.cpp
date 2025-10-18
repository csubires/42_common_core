/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/18 17:55:16 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

Harl::Harl()
{
	std::cout << "The Harl has called the constructor" << std::endl;
}

Harl::~Harl()
{
	std::cout << "The Harl has called the destructor" << std::endl;
}

void Harl::complain(std::string level)
{
	std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	void (Harl::*PtrComplain[4])() =
	{
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	for (int x = 0; x < 4; x++)
	{
		if (level == levels[x])
		{
			(this->*PtrComplain[x])();
			break ;
		}
	}
}

void Harl::filtered_complain(std::string level)
{
	std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };

	int x = -1;
	while (++x < 4)
		if (levels[x].compare(level) == 0)
			break ;

	switch (x)
	{
		case 0:
			this->debug();
			//fallthrough
		case 1:
			this->info();
			//fallthrough
		case 2:
			this->warning();
			//fallthrough
		case 3:
			this->error();
			break ;
		default:
			 std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			 break ;
	}

}

void Harl::debug(void)
{
	std::cout << GREEN << "[ DEBUG ]" << ENDC << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl  << std::endl;;
}
void Harl::info(void)
{
	std::cout << BLUE << "[ INFO ]" << ENDC << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn’t put enough bacon in my burger!" << std::endl;
	std::cout << "If you did, I wouldn’t be asking for more!" << std::endl  << std::endl;;
}
void Harl::warning(void)
{
	std::cout << YELLOW << "[ WARNING ]" << ENDC << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I’ve been coming for years whereas you started working here since last month." << std::endl  << std::endl;;
}
void Harl::error(void)
{
	std::cout << RED << "[ ERROR ]" << ENDC << std::endl;
	std::cout << "This is unacceptable!" << std::endl;
	std::cout << "I want to speak to the manager now." << std::endl;
}
