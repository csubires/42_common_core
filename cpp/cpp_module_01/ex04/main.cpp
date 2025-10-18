/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/20 12:08:53 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

std::string replace(std::string str, std::string s1, std::string s2)
{
	size_t index = 0;

	while (index != std::string::npos)
	{
		index = str.find(s1, index);
		if (index != std::string::npos)
		{
			str.erase(index, s1.length());
			str.insert(index, s2);
			index += s2.length();
		}
	}
	return (str);
}

int main(int argc, char *argv[])
{
	std::string filename;
	std::string s1;
	std::string s2;
	std::string str;

	if (argc != 4)
		return (std::cout << "Bad arguments!" << std::endl, 1);

	filename = argv[1];
	filename += ".replace";
	s1 = argv[2];
	s2 = argv[3];

	if (filename.empty() || s1.empty() || s2.empty())
		return (std::cout << "Bad arguments!" << std::endl, 1);

	std::ifstream input(argv[1]);
	if (!input.is_open())
		return (std::cout << "File Error" << std::endl, 1);

	std::ofstream output(filename.c_str());
	if (!output.is_open())
		return (std::cout << "File Error" << std::endl, 1);


	while (std::getline(input, str))
		output << replace(str, s1, s2) << "\n";

	output.close();
	input.close();
	return (0);
}
