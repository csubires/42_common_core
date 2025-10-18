/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_remove_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:50 by csubires          #+#    #+#             */
/*   Updated: 2024/10/14 16:55:33 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_remove_before(t_dllist **dllist, void (*del)(void*))
{
	t_dllist	*tmp_list;

	if (!dllist || !*dllist)
		return ;
	if (!(*dllist)->next)
	{
		del((*dllist)->data);
		dlist_free((void **)dllist);
		return ;
	}
	tmp_list = (*dllist)->next;
	tmp_list->prev = 0;
	del((*dllist)->data);
	dlist_free((void **)dllist);
	*dllist = tmp_list;
}
