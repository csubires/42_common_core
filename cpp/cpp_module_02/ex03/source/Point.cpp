/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 12:53:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"
#include "../include/Point.hpp"

Point::Point() : x(0), y(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Point::Point(const float x, const float y) : x((float)x), y((float)y)
{
	std::cout << "floating points constructor called" << std::endl;
}

Point::Point(const Point &copy)
{
	*this = copy;
	std::cout << "Copy constructor called" << std::endl;
}

Point const &Point::operator=(Point const &copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
	}
	return (*this);
}

Point::~Point()
{
	std::cout << "Destructor called" <<  std::endl;
}

float	Point::getPointY(void) const
{
	return (this->y.toFloat());
}
float	Point::getPointX(void) const
{
	return (this->x.toFloat());
}

std::ostream & operator<<(std::ostream &ostream,  const Point &points)
{
	ostream << "X = " << points.getPointX() << "; Y = " << points.getPointY() << ";";
	return (ostream);
}
