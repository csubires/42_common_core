/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/12/31 12:44:05 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <iostream>
# include "Fixed.hpp"

class Point
{
	private:
		Fixed x;
		Fixed y;

	public:
		Point();
		~Point();
		Point(float const x, float const y);
		Point(const Point &copy);
		Point const &operator=(Point const &copy);
		float getPointY(void) const;
		float getPointX(void) const;
};

std::ostream	& operator<<(std::ostream &ostream,  const Point &points);
bool			bsp(Point const a, Point const b, Point const c, Point const point);
float			get_triangle_area(Point const a, Point const b, Point const c);

#endif
