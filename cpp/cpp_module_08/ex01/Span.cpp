/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/06/03 07:59:10 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <numeric>
#include "Span.hpp"

Span::Span(unsigned int n): size(n)
{
	container.reserve(n);
}

Span::Span(const Span &obj)
{
	*this = obj;
}

Span	&Span::operator=(const Span &obj)
{
	if (this != &obj)
		container = obj.container;
	return (*this);
}

Span::~Span() { }

void Span::addNumber(int n)
{
	if (container.size() == container.capacity())
		throw FullContainerException();
	container.push_back(n);
}

int Span::shortestSpan()
{
	if (container.size() < 2)
		throw NoSpanException();
	std::vector<int> tmp = container;
	std::sort(tmp.begin(), tmp.end());
	std::adjacent_difference(tmp.begin(), tmp.end(), tmp.begin());
	return (*std::min_element(tmp.begin() + 1, tmp.end()));
}

int Span::longestSpan()
{
	int	range;

	if (container.size() < 2)
		throw NoSpanException();
	range = *std::max_element(container.begin(), container.end()) \
		- *std::min_element(container.begin(), container.end());
	return (range);
}
