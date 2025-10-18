/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:26:04 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"
#include "../include/Dog.hpp"

int main(void)
{
	const Animal* Array[20];
	const Animal* i = new Dog();
	const Animal* j = new Cat();
	delete i;
	delete j;

	std::cout << std::endl;

	for (int x = 0; x < 5; x++) {
		Array[x] = new Dog();
	}

	std::cout << std::endl;

	for (int x= 5; x < 10; x++) {
		Array[x] = new Cat();
	}

	std::cout << std::endl;

	for (int x = 0; x < 10; x++) {
		delete Array[x];
	}

	std::cout << std::endl;

	Dog basic;
	Dog tmp = basic;
}
