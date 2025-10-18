/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_add_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:01 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:24:48 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_add_after(t_dllist **dllist, t_dllist *new)
{
	t_dllist	*tmp_list;

	if (!*dllist)
		dlist_add_before(dllist, new);
	else
	{
		tmp_list = dlist_last(*dllist);
		tmp_list->next = new;
		new->prev = tmp_list;
	}
}
