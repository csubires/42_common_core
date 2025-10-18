/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/07/12 18:26:52 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iterator>
#include <cstddef>

PmergeMe::PmergeMe(std::vector<int> &input, int size): vector(input), deque(input.begin(), input.end()), size(size)
{
	if (size <= 0)
	{
		std::cerr << "Error" << std::endl;
		return ;
	}

	for (int x = 0; x < size; x++)
	{
		if (input[x] < 0)
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
	}

	printContainer(vector, "Before:\t");

	vectorSort();
	dequeSort();
}

PmergeMe::PmergeMe(PmergeMe const &obj) : size(obj.size)
{
	this->vector = obj.vector;
	this->deque = obj.deque;
}

PmergeMe::~PmergeMe()
{ }

PmergeMe &PmergeMe::operator=(PmergeMe const &obj)
{
	if (this != &obj)
	{
		this->vector = obj.vector;
		this->deque = obj.deque;
	}
	return (*this);
}

void PmergeMe::vectorSort()
{
	clock_t start = clock();
	std::vector<int> temp = vector;
	fordJohnsonSort(temp);
	clock_t end = clock();

	printContainer(temp, "After:\t");

	double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << size << " elements with std::vector : "
			  << std::fixed << std::setprecision(5) << duration << " us" << std::endl;
}

void PmergeMe::dequeSort()
{
	clock_t start = clock();
	std::deque<int> temp = deque;
	fordJohnsonSort(temp);
	clock_t end = clock();

	double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << size << " elements with std::deque  : "
			  << std::fixed << std::setprecision(5) << duration << " us" << std::endl;
}

void PmergeMe::fordJohnsonSort(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		return ;

	std::vector<std::pair<int, int> > pairs;
	bool hasOdd = arr.size() % 2 == 1;
	int oddElement = hasOdd ? arr.back() : 0;

	for (size_t x = 0; x < arr.size() - (hasOdd ? 1 : 0); x += 2)
	{
		int a = arr[x];
		int b = arr[x + 1];
		if (a > b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	std::sort(pairs.begin(), pairs.end(), PairComparator());

	std::vector<int> mainChain;
	std::vector<int> pending;

	for (size_t x = 0; x < pairs.size(); x++)
	{
		mainChain.push_back(pairs[x].second);
		pending.push_back(pairs[x].first);
	}

	if (!pending.empty())
	{
		mainChain.insert(mainChain.begin(), pending[0]);
		pending.erase(pending.begin());
	}

	std::vector<int> optimal = optimalInsert(pending.size());
	std::vector<bool> inserted(pending.size(), false);

	for (size_t x = 0; x < optimal.size(); x++)
	{
		int idx = optimal[x];
		if (idx < static_cast<int>(pending.size()) && !inserted[idx])
		{
			binaryInsert(mainChain, pending[idx], 0, mainChain.size() - 1);
			inserted[idx] = true;
		}
	}

	for (size_t x = 0; x < pending.size(); x++)
		if (!inserted[x])
			binaryInsert(mainChain, pending[x], 0, mainChain.size() - 1);

	if (hasOdd)
		binaryInsert(mainChain, oddElement, 0, mainChain.size() - 1);

	arr = mainChain;
}

void PmergeMe::fordJohnsonSort(std::deque<int> &arr)
{
	if (arr.size() <= 1)
		return ;

	std::vector<std::pair<int, int> > pairs;
	bool hasOdd = arr.size() % 2 == 1;
	int oddElement = hasOdd ? arr.back() : 0;

	for (size_t x = 0; x < arr.size() - (hasOdd ? 1 : 0); x += 2)
	{
		int a = arr[x];
		int b = arr[x + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	std::sort(pairs.begin(), pairs.end(), PairComparator());

	std::deque<int> mainChain;
	std::deque<int> pending;

	for (size_t x = 0; x < pairs.size(); x++)
	{
		mainChain.push_back(pairs[x].second);
		pending.push_back(pairs[x].first);
	}

	if (!pending.empty())
	{
		mainChain.push_front(pending[0]);
		pending.pop_front();
	}

	std::vector<int> optimal = optimalInsert(pending.size());
	std::vector<bool> inserted(pending.size(), false);

	for (size_t x = 0; x < optimal.size(); x++)
	{
		int idx = optimal[x];
		if (idx < static_cast<int>(pending.size()) && !inserted[idx])
		{
			binaryInsert(mainChain, pending[idx], 0, mainChain.size() - 1);
			inserted[idx] = true;
		}
	}

	for (size_t x = 0; x < pending.size(); x++)
		if (!inserted[x])
			binaryInsert(mainChain, pending[x], 0, mainChain.size() - 1);

	if (hasOdd)
		binaryInsert(mainChain, oddElement, 0, mainChain.size() - 1);

	arr = mainChain;
}

std::vector<int> PmergeMe::optimalInsert(int n)
{
	std::vector<int> optimal;
	if (n <= 0)
		return (optimal);

	optimal.push_back(0);
	if (n > 1)
		optimal.push_back(1);

	for (int x = 2; x < n; x++)
	{
		int next = optimal[x-1] + 2 * optimal[x-2];
		if (next >= n) break;
		optimal.push_back(next);
	}

	std::vector<int> order;
	for (int x = optimal.size() - 1; x >= 0; x--)
	{
		int start = optimal[x];
		int end = (x == static_cast<int>(optimal.size()) - 1) ? n - 1 : optimal[x + 1] - 1;
		for (int j = end; j >= start; j--)
			order.push_back(j);
	}

	return (order);
}

template<typename Container>
void PmergeMe::binaryInsert(Container &arr, int item, int left, int right)
{
	if (left > right)
	{
		arr.insert(arr.begin() + left, item);
		return ;
	}

	int mid = left + (right - left) / 2;
	if (item <= arr[mid])
		binaryInsert(arr, item, left, mid - 1);
	else
		binaryInsert(arr, item, mid + 1, right);
}

template<typename Container>
void PmergeMe::printContainer(const Container &arr, const std::string &prefix)
{
	std::cout << prefix;
	for (typename Container::const_iterator it = arr.begin(); it != arr.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}
