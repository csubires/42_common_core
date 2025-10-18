/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 10:29:16 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template<typename Arg>
void		swap(Arg &a, Arg &b)
{
	Arg tmp;

	tmp = b;
	b = a;
	a = tmp;
}

template<typename Arg>
const Arg	&min(const Arg &a, const Arg &b)
{
	if(a < b)
		return (a);
	return (b);
}

template<typename Arg>
const Arg	&max(const Arg &a, const Arg &b)
{
	if(a > b)
		return (a);
	return (b);
}

#endif
