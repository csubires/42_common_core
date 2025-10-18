/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/15 09:22:04 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP
# include <algorithm>
# include <iostream>
# include <exception>
# include <vector>

class Span
{
	private:
		size_t				size;
		std::vector<int>	container;
		Span();

	public:
		Span(unsigned int n);
		Span(const Span &obj);
		~Span();
		Span	&operator=(const Span &obj);
		void	addNumber(int n);
		int		shortestSpan();
		int		longestSpan();

	class FullContainerException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Error: Container is full\n");
		}
	};

	template<typename T>
	void addNumber(const typename T::iterator &begin, const typename T::iterator &end)
	{
		if (this->container.size() + std::distance(begin, end) > this->size)
			throw Span::FullContainerException();
		this->container.insert(this->container.end(), begin, end);
	}

	class NoSpanException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Error: No Span valid\n");
		}
	};
};

#endif
