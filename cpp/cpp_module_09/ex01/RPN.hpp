/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/05/30 19:05:27 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <cstdlib>
# include <iostream>
# include <sstream>
# include <stack>
# include <string>

class RPN
{
	private:
		std::string	operation;
		RPN();

	public:
		RPN(std::string operation);
		RPN(const RPN &obj);
		~RPN();
		RPN		&operator=(const RPN &obj);
		void calculate();
};

#endif
