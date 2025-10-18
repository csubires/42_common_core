/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 18:27:13 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <vector>
# include <deque>
# include <ctime>
# include <algorithm>
# include <cstdlib>

struct PairComparator {
	bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const {
		return a.second < b.second;
	}
};

class PmergeMe
{
	public:
		PmergeMe(std::vector<int> &input, int size);
		PmergeMe(const PmergeMe &obj);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &obj);

	private:
		std::vector<int> vector;
		std::deque<int> deque;
		const int size;

		void fordJohnsonSort(std::vector<int> &arr);
		void vectorSort();

		void fordJohnsonSort(std::deque<int> &arr);
		void dequeSort();

		std::vector<int> optimalInsert(int n);

		template<typename Container>
		void binaryInsert(Container &arr, int item, int left, int right);

		template<typename Container>
		void printContainer(const Container &arr, const std::string &prefix);
};

#endif
