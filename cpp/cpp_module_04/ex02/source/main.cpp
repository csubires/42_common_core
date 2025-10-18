/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:27:16 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AbstractAnimal.hpp"
#include "../include/Cat.hpp"
#include "../include/Dog.hpp"

int main(void)
{
	const AbstractAnimal* j = new Dog();
	const AbstractAnimal* i = new Cat();
	std::cout << "Type: " << j->getType() << std::endl;
	std::cout << "Type: " << i->getType() << std::endl;
	j->makeSound();
	i->makeSound();
	delete j;
	delete i;
}
