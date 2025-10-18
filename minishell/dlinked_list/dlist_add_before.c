/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_add_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:00:56 by csubires          #+#    #+#             */
/*   Updated: 2024/10/12 11:37:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_add_before(t_dllist **dllist, t_dllist *new)
{
	new->next = *dllist;
	new->prev = 0;
	if (*dllist)
		(*dllist)->prev = new;
	*dllist = new;
}
