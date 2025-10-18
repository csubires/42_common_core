/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:13:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"

Brain::Brain()
{
	std::cout << GREEN << "Brain Default constructor called" << ENDC << std::endl;
}

Brain::~Brain()
{
	std::cout << RED << "Brain destructor called" << ENDC << std::endl;
}

Brain::Brain(Brain const &copy)
{
	*this = copy;
	std::cout << GREEN << "Brain copy constructor called" << ENDC << std::endl;
}

Brain &Brain::operator=(Brain const &copy)
{
	std::cout << YELLOW << "Brain copy operator assignment called" << ENDC << std::endl;
	if (this != &copy)
	{
		for (int x = 0; x < 100; x++)
		{
			if (!copy.ideas[x].empty())
				ideas[x] = copy.ideas[x];
		}
	}
	return (*this);
}
