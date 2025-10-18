/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/14 10:40:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() { }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &obj)
{
	(void) obj;
	return (*this);
}

ScalarConverter::~ScalarConverter() { }

ScalarConverter::ScalarConverter(const ScalarConverter &obj)
{
	*this = obj;
}

int detect_type(const std::string &str)
{
	if (str == "-inf" || str == "+inf" || str == "nan")
		return (DOUBLE);
	if (str == "-inff" || str == "+inff" || str == "nanf")
		return (FLOAT);
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		return (CHAR);
	if (str.length() == 1 && !std::isdigit(str[0]))
		return (UNKNOWN);
	if (str.length() > 1 && str[str.length() - 1] == 'f')
	{
		std::string temp = str.substr(0, str.length() - 1);
		if (temp.find('.') != std::string::npos)
		{

			char *endptr;
			strtod(temp.c_str(), &endptr);
			if (*endptr == '\0')
				return (FLOAT);
		}
	}

	if (str.find('.') != std::string::npos)
	{
		char *endptr;
		strtod(str.c_str(), &endptr);
		if (*endptr == '\0')
			return (DOUBLE);
	}

	char *endptr;
	long val = strtol(str.c_str(), &endptr, 10);
	if (*endptr == '\0' && val >= std::numeric_limits<int>::min() &&
		val <= std::numeric_limits<int>::max())
		return (INT);

	return (UNKNOWN);
}

void display_char(const std::string &str, int type)
{
	std::cout << "char: ";

	if (type == UNKNOWN || str == "nan" || str == "nanf" ||
		str == "-inf" || str == "+inf" || str == "-inff" || str == "+inff")
	{
		std::cout << "impossible" << std::endl;
		return ;
	}

	char c;
	if (type == CHAR)
	{
		if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
			c = str[1];
		else
			c = str[0];
	}
	else
	{
		int val = static_cast<int>(atoi(str.c_str()));
		if (val < 0 || val > 127)
		{
			std::cout << "impossible" << std::endl;
			return ;
		}
		c = static_cast<char>(val);
	}

	if (c < 32 || c > 126)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
}

void display_int(const std::string &str, int type)
{
	std::cout << "int: ";

	if (type == UNKNOWN || str == "nan" || str == "nanf" ||
		str == "-inf" || str == "+inf" || str == "-inff" || str == "+inff")
	{
		std::cout << "impossible" << std::endl;
		return ;
	}

	if (type == CHAR)
	{
		if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
			std::cout << static_cast<int>(str[1]) << std::endl;
		else
			std::cout << static_cast<int>(str[0]) << std::endl;
	}
	else
	{
		long val = strtol(str.c_str(), NULL, 10);
		if (val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max())
			std::cout << "impossible" << std::endl;
		else
			std::cout << static_cast<int>(val) << std::endl;
	}
}

void display_float(const std::string &str, int type)
{
	std::cout << "float: ";

	if (type == UNKNOWN)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}

	if (str == "nan" || str == "nanf")
	{
		std::cout << "nanf" << std::endl;
		return ;
	}
	if (str == "-inf" || str == "-inff")
	{
		std::cout << "-inff" << std::endl;
		return ;
	}
	if (str == "+inf" || str == "+inff")
	{
		std::cout << "+inff" << std::endl;
		return ;
	}

	float f;
	if (type == CHAR)
	{
		if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
			f = static_cast<float>(str[1]);
		else
			f = static_cast<float>(str[0]);
	}
	else
		f = static_cast<float>(atof(str.c_str()));


	if (f == static_cast<int>(f))
		std::cout << f << ".0f" << std::endl;
	else
		std::cout << f << "f" << std::endl;
}

void display_double(const std::string &str, int type)
{
	std::cout << "double: ";

	if (type == UNKNOWN)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}

	if (str == "nan" || str == "nanf")
	{
		std::cout << "nan" << std::endl;
		return ;
	}
	if (str == "-inf" || str == "-inff")
	{
		std::cout << "-inf" << std::endl;
		return ;
	}
	if (str == "+inf" || str == "+inff")
	{
		std::cout << "+inf" << std::endl;
		return ;
	}

	double d;
	if (type == CHAR)
	{
		if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
			d = static_cast<double>(str[1]);
		else
			d = static_cast<double>(str[0]);
	}
	else
		d = atof(str.c_str());

	if (d == static_cast<int>(d))
		std::cout << d << ".0" << std::endl;
	else
		std::cout << d << std::endl;
}

void ScalarConverter::convert(char *str)
{
	std::string s(str);
	int type = detect_type(s);

	display_char(s, type);
	display_int(s, type);
	display_float(s, type);
	display_double(s, type);
}
