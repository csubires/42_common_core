/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/10 08:42:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP
# include <iostream>
# include <exception>

template <class T>
class Array
{
	private:
		T		*arr;
		size_t	arr_len;

	public:
		Array()
		{
			std::cout << "Array default constructor called" << std::endl;
			arr = NULL;
			arr_len = 0;
		}

		Array(unsigned int n)
		{
			std::cout << "Array constructor called" << std::endl;
			arr = new T[n];
			arr_len = n;
		}

		~Array()
		{
			std::cout << "Array destructor called" << std::endl;
			delete [] arr;
		}

		Array(const Array &obj)
		{
			std::cout << "Array object constructor called" << std::endl;
			arr_len = obj.arr_len;
			arr = new T[arr_len];
			for(size_t x = 0; x < arr_len; x++)
				arr[x] = obj.arr[x];
		}

		Array	&operator=(const Array &obj)
		{
			std::cout << "Array assignation operator called" << std::endl;
			if(this != &obj)
			{
				delete [] arr;
				arr_len = obj.arr_len;
				arr = new T[arr_len];
				for(size_t x = 0; x < arr_len; x++)
					arr[x] = obj.arr[x];
			}
			return (*this);
		}

		T &operator[](int index)
		{
			if(index < 0 || (unsigned int)index >= arr_len)
				throw OutOfRangeException();
			return (arr[index]);
		}

		size_t	size() const
		{
			return (arr_len);
		}

		class OutOfRangeException: public std::exception
		{
			public:
				const char *what() const throw()
				{
					return ("Error: Out Of Range");
				}
		};
	};

#endif
