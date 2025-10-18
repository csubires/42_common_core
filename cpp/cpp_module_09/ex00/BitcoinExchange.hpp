/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 08:35:50 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP
# include <iostream>
# include <algorithm>
# include <cstdlib>
# include <exception>
# include <fstream>
# include <map>
# include <sstream>
# include <limits.h>

# define FILE_DATA "data.csv"

enum e_date { year, month, day };

class BitcoinExchange
{
	private:
		std::string	data;
		std::string input;
		BitcoinExchange();

	public:
		BitcoinExchange(std::string input);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange	&operator=(const BitcoinExchange &obj);
		void	run();
};

#endif
