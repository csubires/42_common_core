/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/30 19:05:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() { }

RPN::RPN(std::string operation)
{
	this->operation = operation;
}

RPN::RPN(const RPN &obj)
{
	*this = obj;
}

RPN::~RPN() { }

RPN	&RPN::operator=(const RPN &obj)
{
	this->operation = obj.operation;
	return (*this);
}

bool	check_str_validity(std::string str)
{
	int	nbr;

	if (str.length() != 1)
		return (0);
	nbr = atoi(str.c_str());
	if(nbr < 0 || nbr >= 10)
		return (0);
	if(str.find_first_not_of("0123456789") != std::string::npos)
		return (0);
	return (1);
}

bool is_operation(std::string str)
{
	if(str == "+" || str == "-" || str == "*" || str == "/")
		return (true);
	return (false);
}

void RPN::calculate()
{
	std::stack<int>		stack;
	std::stringstream	container(this->operation);
	std::string			str;

	try
	{
		while (std::getline(container, str, ' '))
		{
			if(is_operation(str))
			{
				if(stack.size() < 2)
					throw std::exception();
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				if(str == "+")
					stack.push(b + a);
				else if(str == "-")
					stack.push(b - a);
				else if(str == "*")
					stack.push(b * a);
				else if(str == "/")
				{
					if (a == 0)
						throw std::exception();
					stack.push(b / a);
				}
			}
			else
			{
				if(!check_str_validity(str))
					throw std::exception();
				stack.push(atoi(str.c_str()));
			}
		}
		if(stack.size() != 1)
			throw std::exception();
		std::cout << stack.top() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
	}
}
