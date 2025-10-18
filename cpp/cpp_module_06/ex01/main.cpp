/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:50:33 by csubires          #+#    #+#             */
/*   Updated: 2025/07/14 09:07:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>
#include "Serializer.hpp"

void printData(const Data *ptr, const std::string &name)
{
	std::cout << "  " << name << ":\n"
		<< "	n1: " << ptr->n1 << "\n"
		<< "	n2: " << ptr->n2 << "\n"
		<< "	name: " << ptr->name << "\n"
		<< "	addr: " << ptr << std::endl;
}

void testSerialization(Data *original)
{
	std::cout << "\n\033[1;36m[TEST]\033[0m Serializing/Deserializing:\n";
	printData(original, "Original");
	uintptr_t raw = Serializer::serialize(original);
	std::cout << "  Serialized to uintptr_t: " << raw << std::endl;
	Data* restored = Serializer::deserialize(raw);
	printData(restored, "Restored");
	std::cout << "  Comparison: "
		<< (original == restored ? "\033[1;32mSUCCESS\033[0m" : "\033[1;31mFAILED\033[0m")
		<< std::endl;
}

int main() {
	Data data1 = {42, 0, "Hello woorld!"};
	Data data2 = {
		std::numeric_limits<int>::max(),
		0,
		"max & min"
	};
	Data data3 = {0, 0, ""};
	Data *data4 = new Data();
	data4->n1 = -1;
	data4->name = "Memory";

	testSerialization(&data1);
	testSerialization(&data2);
	testSerialization(&data3);
	testSerialization(data4);

	std::cout << "\n\033[1;36m[EXTRA TEST]\033[0m Chain serialization:\n";
	uintptr_t raw1 = Serializer::serialize(&data1);
	uintptr_t raw2 = Serializer::serialize(Serializer::deserialize(raw1));
	Data *finalPtr = Serializer::deserialize(raw2);
	printData(&data1, "Original");
	printData(finalPtr, "After 2x serialization");
	std::cout << "  Comparison: "
		<< (&data1 == finalPtr ? "\033[1;32mSUCCESS\033[0m" : "\033[1;31mFAILED\033[0m")
		<< std::endl;

	delete data4;

	std::cout << "\n\033[1;36m[NULL TEST]\033[0m:\n";
	Data *nullData = NULL;
	uintptr_t nullRaw = Serializer::serialize(nullData);
	Data *restoredNull = Serializer::deserialize(nullRaw);
	std::cout << "  NULL restored as: " << restoredNull << std::endl;
	std::cout << "  Comparison: "
		<< (nullData == restoredNull ? "\033[1;32mSUCCESS\033[0m" : "\033[1;31mFAILED\033[0m")
		<< std::endl;

	return (0);
}
