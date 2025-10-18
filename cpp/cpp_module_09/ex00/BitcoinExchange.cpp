/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 08:37:22 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string input)
{
	this->data = FILE_DATA;
	this->input = input;
}

BitcoinExchange::BitcoinExchange() { }

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	*this = obj;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if(this != &obj)
	{
		this->data = obj.data;
		this->input = obj.input;
	}
	return (*this);
}

std::string&	rtrim(std::string &str)
{
	const char* t = " \t\n\r\f\v";
	str.erase(str.find_last_not_of(t) + 1);
	return (str);
}

std::string&	ltrim(std::string &str)
{
	const char* t = " \t\n\r\f\v";
	str.erase(0, str.find_first_not_of(t));
	return (str);
}

std::string&	trim(std::string &str)
{
	return (ltrim(rtrim(str)));
}

bool	is_valid_date(std::map<int,int> date)
{
	if (date[year] < 1000 || date[year] > 9999)
		return (false);
	if (date[month] < 1 || date[month] > 12)
		return (false);
	if (date[day] < 1 || date[day] > 31)
		return (false);

	if (date[month] == 2)
	{
		bool is_leap = (date[year] % 4 == 0 && date[year] % 100 != 0) || (date[year] % 400 == 0);
		return (date[day] <= (is_leap ? 29 : 28));
	}
	if (date[month] == 4 || date[month] == 6 || date[month] == 9 || date[month] == 11)
		return (date[day] <= 30);
	return (true);
}

bool	check_key_validity(std::string key, int x)
{
	std::stringstream	ss(key);
	std::string			token;
	std::map<int,int>	date;
	int 				count;

	if(key.empty())
		return (false);
	if(!x && key != "date")
		return (false);
	if(x && std::count(key.begin(), key.end(), '-') != 2)
		return (false);
	if(x && key.find_first_not_of("0123456789-") != std::string::npos)
		return (false);
	if(x && (key.find('-') == key.length() - 1 || key.find('-') == 0))
		return (false);
	if(x && key.length() != 10)
		return (false);
	if(x && (key.find_first_of('-') != 4 || key.find_last_of('-') != 7))
		return (false);

	count = 0;
	while(std::getline(ss, token, '-'))
		date[count++] = atoi(token.c_str());
	if(x && is_valid_date(date) == 0)
		return (false);
	return (true);
}

bool	check_value_validity(std::string value, int x, int y)
{
	if(value.empty())
		return (false);
	if(!x && !y && value != "exchange_rate")
		return (false);
	else if(!x && y && value != "value")
		return (false);

	if(x)
	{
		if(value.find_first_not_of("0123456789.") != std::string::npos)
			return (false);
		if(std::count(value.begin(), value.end(), '.') > 1)
			return (false);
		if(value.find('.') == 0 || value.find('.') == value.length() - 1)
			return (false);

		double val = atof(value.c_str());
		if(val < 0)
			return (false);
		if(y && val > 1000)
			return (false);
	}
	return (true);
}

int	convert_to_date(std::string key)
{
	std::stringstream ss(key);
	std::string token;
	std::map<int,int> date;
	int count;

	count = 0;
	while(std::getline(ss, token, '-'))
		date[count++] = atoi(token.c_str());
	return (date[year] * 10000 + date[month] * 100 + date[day]);
}

std::map<int, float>	read_and_parse_data_file(std::string filename)
{
	std::map<int, float> map;
	std::fstream file;
	std::string line;
	int x = 0;

	file.open(filename.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	}

	while (std::getline(file, line))
	{
		int seperator = line.find(',');
		int count = std::count(line.begin(), line.end(), ',');
		if(count != 1 || seperator == -1)
		{
			if(x == 0)
			{
				x++;
				continue;
			}
			std::cerr << "Error: bad data file" << std::endl;
			exit(1);
		}

		std::string key = line.substr(0, seperator);
		std::string value = line.substr(seperator + 1, line.length());
		key = trim(key);
		value = trim(value);

		if(!check_key_validity(key, x) || !check_value_validity(value, x, 0))
		{
			if(x > 0)
			{
				std::cerr << "Error: bad data file" << std::endl;
				exit(1);
			}
		}

		if(x > 0)
		{
			int date = convert_to_date(key);
			float exchange_rate = atof(value.c_str());
			map[date] = exchange_rate;
		}
		x++;
	}
	return (map);
}

void	find_nearest_date(std::map<int, float> data_map, int date, std::string key, std::string value)
{
	std::map<int, float>::iterator it = data_map.lower_bound(date);

	if (it == data_map.begin())
	{
		std::cout << key << " => " << value << " = " << it->second * atof(value.c_str()) << std::endl;
		return;
	}

	--it;
	std::cout << key << " => " << value << " = " << it->second * atof(value.c_str()) << std::endl;
}

void	parse_input_file(std::string filename, std::map<int, float> data_map)
{
	std::fstream file;
	std::string line;
	int x = 0;

	file.open(filename.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	}

	if(file.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	}

	while (std::getline(file, line))
	{
		if(line.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			x++;
			continue;
		}

		int seperator = line.find('|');
		int count = std::count(line.begin(), line.end(), '|');
		if(count != 1 || seperator == -1)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			x++;
			continue;
		}

		std::string key = line.substr(0, seperator);
		key = trim(key);
		std::string value = line.substr(seperator + 1, line.length());
		value = trim(value);

		if(x == 0)
		{
			x++;
			continue;
		}

		if(!check_key_validity(key, x))
		{
			std::cerr << "Error: bad input => " << key << std::endl;
			x++;
			continue;
		}

		if(!check_value_validity(value, x, 1))
		{
			double val = atof(value.c_str());
			if(val < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else if(val > 1000)
				std::cerr << "Error: too large a number." << std::endl;
			else
				std::cerr << "Error: bad input => " << value << std::endl;
			x++;
			continue;
		}

		int date = convert_to_date(key);
		if(data_map.find(date) == data_map.end())
			find_nearest_date(data_map, date, key, value);
		else
			std::cout << key << " => " << value << " = " << data_map[date] * atof(value.c_str()) << std::endl;

		x++;
	}
}

void	BitcoinExchange::run()
{
	std::map<int, float> data_map = read_and_parse_data_file(data);
	parse_input_file(input, data_map);
}
