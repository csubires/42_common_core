/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2025/01/01 10:49:48 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MATERIASOURCE_HPP_
#define _MATERIASOURCE_HPP_

#include "AMateria.hpp"

typedef std::string str;

class IMateriaSource
{
	public:
		virtual ~IMateriaSource();

		virtual void		getMemory() const = 0;
		virtual void		learnMateria(AMateria *materia) = 0;
		virtual AMateria *	createMateria(str const &type) = 0;
};

class MateriaSource : public IMateriaSource
{
	public:
		MateriaSource();
		MateriaSource(MateriaSource const &src);
		virtual	~MateriaSource();

		MateriaSource 		&operator=(MateriaSource const &rSym);
		virtual void		getMemory() const;
		virtual void		learnMateria(AMateria *materia);
		virtual AMateria	*createMateria(str const &type);

	private:
		int			_idxTotal;
		AMateria *	_memory[4];
};

#endif
