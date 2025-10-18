/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/02/15 11:19:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include "../include/WrongAnimal.hpp"
#include "../include/WrongCat.hpp"

int main()
{

	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << "Type: " << meta->getType() << " " << std::endl;
	std::cout << "Type: " << j->getType() << " " << std::endl;
	std::cout << "Type: " << i->getType() << " " << std::endl;
	meta->makeSound();
	j->makeSound();
	i->makeSound();
	delete meta;
	delete j;
	delete i;

	std::cout << std::endl;

	Animal animal;
	Animal animal1(Animal("unidentified"));
	animal = animal1;
	std::cout << "Type: " << animal.getType() << std::endl;
	animal.makeSound();
	std::cout << "Type: " << animal1.getType() << std::endl;
	animal1.makeSound();

	std::cout << std::endl;

	Cat cat;
	Cat cat1((Cat()));
	cat = cat1;
	std::cout << "Type: " << cat.getType() << std::endl;
	cat.makeSound();
	std::cout << "Type: " << cat1.getType() << std::endl;
	cat1.makeSound();

	std::cout << std::endl;

	Dog dog;
	Dog dog1((Dog()));
	dog = dog1;
	std::cout << "Type: " << dog.getType() << std::endl;
	dog.makeSound();
	std::cout << "Type: " << dog1.getType() << std::endl;
	dog1.makeSound();

	std::cout << std::endl;

	WrongAnimal wrongAnimal;
	WrongCat wrongCat;
	WrongAnimal wrongAnimal1(wrongAnimal);
	WrongCat wrongCat1(wrongCat);
	wrongAnimal = wrongAnimal1;
	wrongCat = wrongCat1;
	const WrongAnimal*	meta1 = new WrongAnimal();
	std::cout << "Type: " << meta1->getType() << std::endl;
	const WrongAnimal*	i1 = new WrongCat();
	std::cout << "Type: " << i1->getType() << std::endl;
	meta1->makeSound();
	i1->makeSound();
	delete i1;
	delete meta1;
}
