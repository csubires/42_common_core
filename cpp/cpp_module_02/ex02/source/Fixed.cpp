/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 12:36:35 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() : value(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy)
{
	*this = copy;
	// std::cout << "Copy constructor called" << std::endl;
}

Fixed::~Fixed()
{
	// std::cout << "Destructor called" <<  std::endl;
}

Fixed &Fixed::operator=(const Fixed &copy)
{
	// std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		value = copy.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	return (value);
}

void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

Fixed::Fixed(const int value)
{
	this->value = (int)roundf((value * (1 << fractional_value)));
	// std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float float_nbr)
{
	this->value = (int)roundf(float_nbr * (1 << this->fractional_value));
	// std::cout << "Float constructor called" << std::endl;
}

float Fixed::toFloat(void) const
{
	return((float)this->value / (float)(1 << this->fractional_value));
}

int Fixed::toInt(void) const
{
	return((int)roundf(this->value / (1 << this->fractional_value)));
}

std::ostream & operator<<(std::ostream &ostream,  const Fixed &value)
{
	ostream << value.toFloat();
	return (ostream);
}

bool Fixed::operator>(const Fixed &f2)
{
	if (this->value > f2.value)
		return (true);
	else
		return (false);
}

bool Fixed::operator<(const Fixed &f2)
{
	if (this->value < f2.value)
		return (true);
	else
		return (false);
}

bool Fixed::operator>=(const Fixed &f2)
{
	if (this->value >= f2.value)
		return (true);
	else
		return (false);
}

bool Fixed::operator<=(const Fixed &f2)
{
	if (this->value <= f2.value)
		return (true);
	else
		return (false);
}

bool Fixed::operator==(const Fixed &f2)
{
	if (this->value == f2.value)
		return (true);
	else
		return (false);
}

bool Fixed::operator!=(const Fixed &f2)
{
	if (this->value != f2.value)
		return (true);
	else
		return (false);
}

float Fixed::operator+(const Fixed &f2)
{
	float x = (float)this->value / (float)(1 << this->fractional_value);
	x += (float)f2.value / (float)(1 << f2.fractional_value);
	return (x);
}

float Fixed::operator-(const Fixed &f2)
{
	float x = (float)this->value / (float)(1 << this->fractional_value);
	x -= (float)f2.value / (float)(1 << f2.fractional_value);
	return (x);
}

float Fixed::operator*(const Fixed &f2)
{
	float x = (float)this->value / (float)(1 << this->fractional_value);
	x *= (float)f2.value / (float)(1 << f2.fractional_value);
	return (x);
}

float Fixed::operator/(const Fixed &f2)
{
	float x = (float)this->value / (float)(1 << this->fractional_value);
	x /= (float)f2.value / (float)(1 << f2.fractional_value);
	return (x);
}

Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	++value;
	return (temp);
}

Fixed Fixed::operator++()
{
	++value;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	--value;
	return (temp);
}

Fixed Fixed::operator--()
{
	--this->value;
	return (*this);
}

Fixed Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1.value < f2.value)
		return (f1);
	else
		return (f2);
}

Fixed const Fixed::min(Fixed const &f1, Fixed const &f2)
{
	if (f1.value < f2.value)
		return (f1);
	else
		return (f2);
}

Fixed Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1.value > f2.value)
		return (f1);
	else
		return (f2);
}

Fixed const Fixed::max(Fixed const &f1, Fixed const &f2)
{
	if (f1.value > f2.value)
		return (f1);
	else
		return (f2);
}
