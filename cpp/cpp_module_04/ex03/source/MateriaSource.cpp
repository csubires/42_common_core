/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:58:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MateriaSource.hpp"

MateriaSource::MateriaSource() : _idxTotal(0)
{
	std::cout << "[C] MateriaSource default constructor called." << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
	std::cout << "[C] MateriaSource copy constructor called." << std::endl;
	*this = src;
}

MateriaSource::~MateriaSource()
{
	std::cout << "[D] MateriaSource default destructor called." << std::endl;
	int idx = -1;
	while (++idx < this->_idxTotal)
		delete this->_memory[idx];
}

IMateriaSource::~IMateriaSource()
{
	std::cout << "[D] IMateriaSource interface default destructor called." << std::endl;
}

MateriaSource &MateriaSource::operator=(MateriaSource const &rSym)
{
	if (this != &rSym) {
		this->_idxTotal = rSym._idxTotal;
		int idx = -1; while (++idx < 4)
			this->_memory[idx] = rSym._memory[idx];
	}
	return (*this);
}

void MateriaSource::getMemory() const
{
	std::cout << "MateriaSource's memory contain :" << std::endl;
	int	idx = -1; while (++idx < _idxTotal)
		std::cout << "\t[" << idx << "] " << this->_memory[idx]->getType() << std::endl;
}

void MateriaSource::learnMateria(AMateria *materia)
{
	if (this->_idxTotal == 4) {
		std::cout << "MateriaSource is full of memory. Can't add a new AMateria model." << std::endl; return;
	}
	this->_memory[_idxTotal] = materia;
	this->_idxTotal++;
}

AMateria *MateriaSource::createMateria(str const &type)
{
	int	idx = -1;
	while (++idx < _idxTotal)
	{
		if (this->_memory[idx]->getType() == type)
			return this->_memory[idx];
	}
	std::cout << "This MateriaSource don't have the type : " << type << " in memory." << std::endl;
	return (0);
}
