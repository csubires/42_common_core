/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 12:30:29 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <math.h>

class Fixed
{
	private :
		int					value;
		static const int	fractional_value = 8;

	public:
		Fixed();
		Fixed(const Fixed &copy);
		Fixed(const int value);
		Fixed(const float float_nbr);
		~Fixed();

		bool	operator>(const Fixed &f2);
		bool	operator<(const Fixed &f2);
		bool	operator>=(const Fixed &f2);
		bool	operator<=(const Fixed &f2);
		bool	operator==(const Fixed &f2);
		bool	operator!=(const Fixed &f2);
		float	operator+(const Fixed &f2);
		float	operator-(const Fixed &f2);
		float	operator*(const Fixed &f2);
		float	operator/(const Fixed &f2);
		Fixed	&operator=(const Fixed &copy);
		Fixed	operator++(int);
		Fixed	operator++();
		Fixed	operator--(int);
		Fixed	operator--();
		static Fixed min(Fixed &f1, Fixed &f2);
		static Fixed const min(Fixed const &f1, Fixed const &f2);
		static Fixed max(Fixed &f1, Fixed &f2);
		static Fixed const max(Fixed const &f1, Fixed const &f2);
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;
};

std::ostream	& operator<<(std::ostream &ostream,  const Fixed &value);

#endif
