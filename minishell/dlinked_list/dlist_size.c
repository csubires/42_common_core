/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:56 by csubires          #+#    #+#             */
/*   Updated: 2024/11/12 12:36:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

size_t	dlist_size(t_dllist *dlst)
{
	size_t	x;

	x = 0;
	while (dlst)
	{
		x++;
		dlst = dlst->next;
	}
	return (x);
}
