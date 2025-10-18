/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 11:15:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP
# include <iostream>

template <typename T>
void iter(const T *arr, size_t len, void(*f)(const T&))
{
	for(size_t x = 0;x < len; x++)
		f(arr[x]);
}

template <typename T>
void iter(T *arr, size_t len, void(*f)(T&))
{
	for(size_t x = 0; x < len; x++)
		f(arr[x]);
}

#endif
